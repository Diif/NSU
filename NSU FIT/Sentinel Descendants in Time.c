#include <stdio.h>
#include <malloc.h>

typedef struct switch_s{
    int* lamps_inf;
}swit;

typedef struct conroller_s{
    swit* switches;
    int* sw_state;
}controller;

typedef struct wrap_s{
    controller* controllers;
}wrap;

int find_sol(int* cur_lamp_volt, wrap* wrapper,int cur_contr,
             int max_contr, int max_swtch, int max_lamps, int max_volt) {
    int s;
    if(cur_contr == max_contr-1){
        int kas = 1;
    }
    for(s = 0; s < max_swtch; s++) {
        wrapper->controllers[cur_contr].sw_state[s] = 1;

        for (int i = 0; i < max_lamps; i++) {

            cur_lamp_volt[i] = cur_lamp_volt[i] +
                               wrapper->controllers[cur_contr].switches[s].lamps_inf[i];

            if (cur_lamp_volt[i] > max_volt) {
                wrapper->controllers[cur_contr].sw_state[s] = 0;
                for (int j = 0; j <= i; j++) {
                    cur_lamp_volt[j] = cur_lamp_volt[j] -
                                       wrapper->controllers[cur_contr].switches[s].lamps_inf[j];
                }
                break;
            }
        }
            if (cur_contr < max_contr - 1 && wrapper->controllers[cur_contr].sw_state[s] == 1) {
                if (find_sol(cur_lamp_volt, wrapper, cur_contr + 1, max_contr, max_swtch, max_lamps, max_volt)) {
                    return 1;
                } else {
                    for (int m = 0; m < max_lamps; m++){
                        cur_lamp_volt[m] = cur_lamp_volt[m] -
                                           wrapper->controllers[cur_contr].switches[s].lamps_inf[m];
                    }
                    wrapper->controllers[cur_contr].sw_state[s] = 0;
                }
            } else if (cur_contr == max_contr -1 && wrapper->controllers[cur_contr].sw_state[s] == 1){
                for (int i = 0; i < max_lamps; i++){
                    if(cur_lamp_volt[i] != max_volt){
                        for (int m = 0; m < max_lamps; m++){
                            cur_lamp_volt[m] = cur_lamp_volt[m] -
                                               wrapper->controllers[cur_contr].switches[s].lamps_inf[m];
                        }
                        wrapper->controllers[cur_contr].sw_state[s] = 0;
                        break;
                    }
                }
            }
        if(wrapper->controllers[cur_contr].sw_state[s] == 1) {
            return 1;
        }
    }
    return 0;
}

int main(){
    FILE* in, *out;

    in = fopen(PATH"/input.txt", "r");
    out = fopen(PATH"/output.txt", "w");

    int contr_amt, swtch_amt, lamps_amt, req_volt;
    char buf;

    fscanf(in, "%d%d%d%d", &contr_amt, &swtch_amt, &lamps_amt,&req_volt);

    wrap* wrapper = (wrap*)malloc(sizeof(wrap));
    wrapper->controllers = (controller*)malloc(sizeof(controller)*contr_amt);
    int* cur_lamps = (int*)malloc(sizeof(int)*lamps_amt);

    for(int i = 0; i < lamps_amt; i++){
        cur_lamps[i] = 0;
    }

    for(int i =0; i < contr_amt; i++){
        wrapper->controllers[i].switches = (swit*)malloc(sizeof(swit)*swtch_amt);
        wrapper->controllers[i].sw_state = (int*)malloc(sizeof(int)*swtch_amt);
    }
    for(int i =0; i < contr_amt; i++){
        for (int j = 0; j < swtch_amt; ++j) {
            wrapper->controllers[i].switches[j].lamps_inf = (int*)malloc(sizeof(int)*lamps_amt);
            for(int k = 0; k < swtch_amt; k++){
                wrapper->controllers[i].sw_state[k] = 0;
            }
        }
    }

    for(int cntr = 0, swt = 0, lmp = 0; cntr < contr_amt;){
        fscanf(in,"%c", &buf);

        if(buf != 'X' && buf !='.'){
            continue;
        } if (buf == EOF){
            break;
        }

        if(buf == 'X'){
            wrapper->controllers[cntr].switches[swt].lamps_inf[lmp] = 1;
        } else {
            wrapper->controllers[cntr].switches[swt].lamps_inf[lmp] = 0;
        }
        if(lmp == lamps_amt-1){
            lmp = 0;
            swt++;
        } else {
            lmp++;
        }
        if (swt == swtch_amt){
            swt = 0;
            cntr++;
        }
    }

    if(find_sol(cur_lamps,wrapper,0,contr_amt,swtch_amt,lamps_amt,req_volt)){

        fprintf(out,"YES\n");
        for(int i = 0; i < contr_amt; i++){
            for(int j = 0; j < swtch_amt; j++){
                if(wrapper->controllers[i].sw_state[j] == 1){
                    fprintf(out,"%d\n", j+1);
                    break;
                }
            }
        }
    } else {
        fprintf(out,"NO\n");
    }
}