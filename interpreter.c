#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char *document = "int ayy = 10\nint byy = 9\nint ccl = 2\nadd ayy 12\n\0";
    char line_seg[5][10];


    //Used to step through the document(program)
    int document_pointer = 0;
    //Which segment of line we are on
    int segment_pointer = 0;
    //Which bit of the segment we are on
    int str_pointer = 0;

    char current_char = document[document_pointer];

    int var_pointer = 0;
    char var_names[20][10];
    int var_value[20];

    while(current_char != '\0'){
      if(current_char != '\n'){
        if(current_char != ' '){
          line_seg[segment_pointer][str_pointer++] = current_char;
        }else{
          segment_pointer++;
          str_pointer = 0;
        }
      }else{
        //Process line
        int index;
        for(index=0; index<segment_pointer; index++){
          if(strcmp(line_seg[index], "int") == 0){
            //Declaring a variable
            char *name = line_seg[index+1];
            int value = atoi(line_seg[index+3]);
            strcpy(var_names[var_pointer], name);
            var_value[var_pointer] = value;
            var_pointer++;
            break;
          }
          if(strcmp(line_seg[index], "add") == 0){
            char *pool = line_seg[index+1];
            char *drop = line_seg[index+2];
            int v_index;

            int pool_index = -1;
            int drop_index = -1;
            int both_vars = 0;
            for(v_index=0; v_index<var_pointer; v_index++){
              if(strcmp(pool, var_names[v_index]) == 0){
                pool_index = v_index;
              }
              if(strcmp(drop, var_names[v_index]) == 0){
                drop_index = v_index;
              }
              if(drop_index != -1 && pool_index != -1){
                both_vars = 1;
                break;
              }
            }

            if(both_vars == 1){
              var_value[pool_index] += var_value[drop_index];
            }else if(pool_index == -1){
              printf("Error, need memory to add variable to");
            }else if(drop_index == -1){
              int drop_input = atoi(drop);
              var_value[pool_index] += drop_input;
            }


          }
        }
        segment_pointer = 0;
        str_pointer = 0;
        memset(line_seg, 0, sizeof line_seg);
      }
      current_char = document[++document_pointer];
    }

    int i;
    for(i=0; i<var_pointer; i++){
      printf("Name: %s\n", var_names[i]);
      printf("Value: %i\n", var_value[i]);
    }


    return 0;
}
