#include <math.h>
#include <memory.h>
#include <mpi.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define L 2500
#define MAX_ITERS 50

#define RECEIVER_TAG 1
#define END_THREAD 2
#define NO_TASKS 0
#define WORKER_TAG 4

pthread_t rec_thread;
pthread_mutex_t mutex;

int provided;
int size, rank;
double global_res;
int global_iter;
int list_size;
int last_task;
int cur_task;
int* task_list;
int* additional_tasks_list;
double* iteration_work_time;

void InitGlobalVars();
void WorkerThreadJob();
void AskForTasks();
void* ReceiverThreadJob(void*);

int main(int argc, char** argv) {
  MPI_Init_thread(&argc, &argv, MPI_THREAD_MULTIPLE, &provided);
  if (provided != MPI_THREAD_MULTIPLE) {
    exit(EXIT_FAILURE);
  }
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  pthread_attr_t attr;
  if (pthread_attr_init(&attr)) {
    exit(EXIT_FAILURE);
  }

  if (pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE)) {
    exit(EXIT_FAILURE);
  }

  InitGlobalVars();
  pthread_mutexattr_t mut_attr;
  pthread_mutexattr_init(&mut_attr);
  pthread_mutex_init(&mutex, &mut_attr);
  pthread_mutexattr_destroy(&mut_attr);

  if (pthread_create(&rec_thread, &attr, ReceiverThreadJob, NULL)) {
    exit(EXIT_FAILURE);
  }

  pthread_attr_destroy(&attr);

  WorkerThreadJob();
  if (pthread_join(rec_thread, NULL)) {
    exit(EXIT_FAILURE);
  }

  // if (rank == 0) {
  // fprintf(stderr, "globalres %lf", global_res);
  // }

  MPI_Finalize();
}

void CreateNewTasks() {
  srand(time(NULL));
  for (int i = 0; i < list_size; i++) {
    task_list[i] =
        // 100;
        abs(50 - i % 100) * abs(rank - (global_iter + 1 % (size + 1))) * L;
    // rand() % 200;
    // if (task_list[i] < 0) {
    //   task_list[i] *= -1;
    // }
  }
}

void InitGlobalVars() {
  global_res = 0;
  global_iter = 0;
  list_size = size * 100;
  last_task = list_size - 1;
  cur_task = last_task;
  task_list = (int*)malloc(sizeof(int) * list_size);
  additional_tasks_list = (int*)malloc(sizeof(int) * size);
  additional_tasks_list[rank] = NO_TASKS;
  if (rank == 0) {
    iteration_work_time = (double*)malloc(sizeof(double) * size);
  }
}

void AskForTasks() {
  int code = RECEIVER_TAG;
  for (int i = 0; i < size; i++) {
    if (i != rank) {
      MPI_Send(&code, 1, MPI_INT, i, RECEIVER_TAG, MPI_COMM_WORLD);
    }
  }
  code = NO_TASKS;
  for (int i = 0; i < size; i++) {
    if (i != rank) {
      MPI_Recv(additional_tasks_list + i, 1, MPI_INT, i, WORKER_TAG,
               MPI_COMM_WORLD, MPI_STATUS_IGNORE);
    }
  }
  int task_counter = 0;
  pthread_mutex_lock(&mutex);
  for (int i = 0; i < size; i++) {
    if (additional_tasks_list[i] != NO_TASKS) {
      task_list[task_counter] = additional_tasks_list[i];
      task_counter++;
    }
  }
  if (task_counter) {
    cur_task = 0;
    last_task = task_counter - 1;
  }
  pthread_mutex_unlock(&mutex);
}

void ProcessRes(double work_time, int num_tasks) {
  MPI_Gather(&work_time, 1, MPI_DOUBLE, iteration_work_time, 1, MPI_DOUBLE, 0,
             MPI_COMM_WORLD);
  double min_time, max_time;
  if (rank == 0) {
    min_time = iteration_work_time[0];
    max_time = iteration_work_time[0];
    for (int i = 0; i < size; i++) {
      if (min_time > iteration_work_time[i]) {
        min_time = iteration_work_time[i];
      }
      if (max_time < iteration_work_time[i]) {
        max_time = iteration_work_time[i];
      }
    }
  }

  if (rank == 0) {
    fprintf(
        stderr,
        "\t\tIteration %d, global res %lf, max %lf, min %lf, disb_time %lf, "
        "disb_part %lf%%\n",
        global_iter, global_res, max_time, min_time, max_time - min_time,
        (max_time - min_time) / max_time * 100);
  }

  for (int i = 0; i < size; i++) {
    MPI_Barrier(MPI_COMM_WORLD);
    if (i == rank) {
      fprintf(stderr, "Proc %d, global res %lf, work time %lf, tasks %d\n",
              rank, global_res, work_time, num_tasks);
    }
  }
}

void WorkerThreadJob() {
  double local_res = 0;
  while (global_iter < MAX_ITERS) {
    pthread_mutex_lock(&mutex);
    CreateNewTasks();
    int tasks_on_iter = 0;
    cur_task = 0;
    last_task = list_size - 1;
    pthread_mutex_unlock(&mutex);
    local_res = 0;
    double start = MPI_Wtime();

    while (1) {
      pthread_mutex_lock(&mutex);
      if (!(cur_task <= last_task)) {
        pthread_mutex_unlock(&mutex);
        break;
      }
      pthread_mutex_unlock(&mutex);
      while (1) {
        pthread_mutex_lock(&mutex);
        if (!(cur_task <= last_task)) {
          pthread_mutex_unlock(&mutex);
          break;
        }
        pthread_mutex_unlock(&mutex);
        for (int i = 0, count = task_list[cur_task]; i < count; i++) {
          local_res += 1;  // sin(i);
        }
        pthread_mutex_lock(&mutex);
        tasks_on_iter++;
        cur_task++;
        pthread_mutex_unlock(&mutex);
      }
      AskForTasks();
    }
    double work_time = MPI_Wtime() - start;
    global_iter++;
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Allreduce(&local_res, &global_res, 1, MPI_DOUBLE, MPI_SUM,
                  MPI_COMM_WORLD);
    ProcessRes(work_time, tasks_on_iter);
    MPI_Barrier(MPI_COMM_WORLD);
  }
  int code = END_THREAD;
  MPI_Send(&code, 1, MPI_INT, rank, RECEIVER_TAG, MPI_COMM_WORLD);
  MPI_Barrier(MPI_COMM_WORLD);
  // MPI_Allreduce(&local_res, &global_res, 1, MPI_DOUBLE, MPI_SUM,
  //               MPI_COMM_WORLD);
}

void* ReceiverThreadJob(void* t) {
  while (1) {
    int code;
    MPI_Status status;
    MPI_Recv(&code, 1, MPI_INT, MPI_ANY_SOURCE, RECEIVER_TAG, MPI_COMM_WORLD,
             &status);
    if (status.MPI_SOURCE == rank && code != END_THREAD) {
      exit(EXIT_FAILURE);
    }
    if (code == END_THREAD) {
      break;
    }
    pthread_mutex_lock(&mutex);
    int remaining_tasks = last_task - cur_task;
    if (remaining_tasks <= 0) {
      pthread_mutex_unlock(&mutex);
      code = NO_TASKS;
      MPI_Send(&code, 1, MPI_INT, status.MPI_SOURCE, WORKER_TAG,
               MPI_COMM_WORLD);
      continue;
    }
    int task_to_send = task_list[last_task];
    last_task--;
    pthread_mutex_unlock(&mutex);
    MPI_Send(&task_to_send, 1, MPI_INT, status.MPI_SOURCE, WORKER_TAG,
             MPI_COMM_WORLD);
  }
}
