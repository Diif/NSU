#include <stdio.h>
#include <stdlib.h>

struct edge_s;

typedef struct vertex_s{
    int num;
    struct edge_s* child;
    struct edge_s* last_child;
}vertex;

typedef struct edge_s{
    vertex* vrt;
    int weight;
    struct edge_s* next;
}edge;

typedef struct cost_to_vertex_s{
    vertex* vrt;
    int cost;
    int heap_id;//для операции уменьшения ключа
}cost_to_vrt;

typedef struct heap{
    cost_to_vrt** mas;
    int size;
    int amt;
}heap_s;


heap_s* h_init(int size){
    heap_s* h = (heap_s*)malloc(sizeof(heap_s));
    h->size = size;
    h->amt = 0;
    h->mas = (cost_to_vrt**)malloc(sizeof(int)*(size+1));
    return h;
}
int h_is_empty(heap_s* h){
    return !(h->amt);
}
int parent(int ind){
    if (ind % 2 == 0) {
        return (ind) / 2;
    }
    return (ind-1) / 2;
}

void swap(int ind1, int ind2, heap_s* h){
    cost_to_vrt* buf = h->mas[ind1];
    int buf_id = h->mas[ind1]->heap_id;
    h->mas[ind1]->heap_id = h->mas[ind2]->heap_id;
    h->mas[ind2]->heap_id = buf_id;
    h->mas[ind1] = h->mas[ind2];
    h->mas[ind2] = buf;
}

int left(int ind, heap_s* h){
    if(ind*2 <= h->amt) {
        return ind * 2;
    }
    return -1;
}

int right(int ind, heap_s* h){
    if((ind*2)+1 <= h->amt) {
        return (ind * 2)+1;
    }
    return -1;
}

void sift_up(int ind, heap_s* h){
    if (ind == 1){
        return;
    }

    if( h->mas[ind]->cost < h->mas[parent(ind)]->cost) {
        swap(ind, parent(ind), h);
        sift_up(parent(ind), h);
    }
}

void sift_down(int ind, heap_s* h){
    if (ind == (h->amt)){
        return;
    }

    int min;
    int num = h->mas[ind]->cost;

    int ileft = left(ind,h);
    int iright = right(ind,h);

    if (ileft > 0 && h->mas[ileft]->cost < num){
        min = ileft;
    } else {
        min = ind;
    }
    if(iright > 0 && h->mas[iright]->cost < h->mas[min]->cost){
        min = iright;
    }
    if (min != ind){
        swap(min,ind,h);
        sift_down(min,h);
    }
}

cost_to_vrt* pop(heap_s* h) {//TODO add "cant find" error
    /*if (h_is_empty(h)){
        return NULL;
    }*/
    cost_to_vrt* buf = h->mas[1];
    h->mas[1] = h->mas[(h->amt)];
    h->mas[1]->heap_id = 1;
    h->amt--;
    sift_down(1,h);
    return buf;
}

void push(heap_s* h, cost_to_vrt* data){//TODO add overflow check
    h->amt++;
    h->mas[h->amt] = data;
    h->mas[h->amt]->heap_id = h->amt;
    sift_up((h->amt),h);
}

void connect_vrts(vertex* from, vertex* to, int path_cost){
    edge* to_v1 = (edge*)malloc(sizeof(edge));
    edge* to_v2 = (edge*)malloc(sizeof(edge));

    to_v1->next = NULL;
    to_v1->weight = path_cost;
    to_v1->vrt = from;

    to_v2->next = NULL;
    to_v2->weight = path_cost;
    to_v2->vrt = to;

    if(from->last_child){
        from->last_child->next = to_v2;
        from->last_child = to_v2;
    }else{
        from->child = to_v2;
        from->last_child = to_v2;
    }

    if(to->last_child){
        to->last_child->next = to_v1;
        to->last_child = to_v1;
    }else{
        to->child = to_v1;
        to->last_child = to_v1;
    }

}

void init_graph(vertex* graph, int size){
    for (int i = 0; i < size; ++i) {
        graph[i].child = NULL;
        graph[i].last_child = NULL;
        graph[i].num = i;
    }
}

void decrease_key(heap_s* h, int id, int res_val){
    h->mas[id]->cost = res_val;
    sift_up(id,h);
}

void Dijkstra_alg(int size, cost_to_vrt* res, int start){
    heap_s* h = h_init(size);
    vertex* cur_vrt;
    edge* cur_edge;

    push(h, &(res[start]));
    int dest_vert_id;

    while(!h_is_empty(h)){
        cur_vrt = pop(h)->vrt;
        cur_edge = cur_vrt->child;
        while (cur_edge){//бежим по всем ребрам текущей вершины
            dest_vert_id = cur_edge->vrt->num;
            if(dest_vert_id != cur_vrt->num) {//петли бесполезны, пропускаем их
                if (res[dest_vert_id].cost == -1) {//если не было пути в вершину
                    res[dest_vert_id].cost = cur_edge->weight+res[cur_vrt->num].cost;
                    push(h,&(res[dest_vert_id]));
                } else if (res[dest_vert_id].cost > res[cur_vrt->num].cost + cur_edge->weight) {//если новый путь короче пред-го
                    decrease_key(h,res[dest_vert_id].heap_id,res[cur_vrt->num].cost + cur_edge->weight);
                }
            }//следующее ребро
            cur_edge = cur_edge->next;
        }
    }

}
int main() {
    FILE* in = fopen(PATH"/input.txt", "r");
    FILE* out = fopen(PATH"/output.txt", "w");


    int num_vertices, start_vert, finish_vert, from, to, cost;

    fscanf(in,"%d",&num_vertices);

    cost_to_vrt* res = (cost_to_vrt*)malloc(sizeof(cost_to_vrt)*num_vertices);
    vertex* graph = (vertex*)malloc(sizeof(vertex)*num_vertices);
    
    fscanf(in,"%d%d", &start_vert,&finish_vert);
    start_vert--;
    finish_vert--;

    init_graph(graph,num_vertices);
    
    while (fscanf(in,"%d%d%d",&from,&to,&cost) > 0) {
        to--;
        from--;
        connect_vrts(&(graph[from]),&(graph[to]),cost);
    }

    for(int i = 0; i < num_vertices;i++){
        res[i].cost = -1;
        res[i].vrt = &(graph[i]);
    }
    res[start_vert].cost=0;

    Dijkstra_alg(num_vertices,res,start_vert);

    if(res[finish_vert].cost != -1) {
        fprintf(out, "%d", res[finish_vert].cost);
    }
    else{
        fprintf(out, "no");
    }

    fclose(in);
    fclose(out);
    return 0;
}
