/*

*/

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void fork_exec_pipe(char **cmd, int pipe_input, int pipe_output){
  pid_t pid = fork(); // processus fils
  if (pid==0){
    dup2(); // stdout -> pipe
    dup2(); // pipe -> stdin
    execvp(cmd[0], cmd); // execute la commande
  }
}

int shell_parse(char **args, char* line){

  char* token;
  int arg_count=0;
  int pipe_idx=0;

  // strsep renvoie le premier morceau avant séparateur, et rend ce qui reste dans 
  // la ligne de départ.
  while ((token = strsep(&line, " ")) != NULL) {
    if (token[0]=='|'){
      // pipe detecté
      pipe_idx = arg_count;
      continue;
    }
    args[arg_count] = token;
    arg_count++;
  }
  // une liste d'argv (pour execv par exemple) finit toujours par NULL.
  args[arg_count] = NULL;


  return pipe_idx;
}

void shell_loop(void){

  char line[256];
  char *args[64];
  char *arg1_pipe[64];
  int pipe_idx;
  int pipe_fds[2];
  int i;

  while(1) {
    printf("\n$ ");
    fgets(line, 256, stdin);
    line[strcspn(line, "\n")] = 0;
    pipe_idx = shell_parse(args, line);

    ///// CD
    if (!strcmp(args[0], "cd")){
      // le pwd est associé au processus. Quand on fork, on change de processus. Donc le cd prend
      // effet sur le child, pas sur le parent ! besoin d'un cd "builtin"
      chdir(args[1]);
    }

    ///// PIPE OR NO PIPE ?
    if (pipe_idx){

      printf("pipe");

      for (i = 0 ; i<pipe_idx ; i++){
        arg1_pipe[i] = args[i];
      }
      arg1_pipe[i]=NULL;

      pipe(pipe_fds); // pipefds0=target, pipefds1=source
      fork_exec_pipe(arg1_pipe, 0, pipe_fds[1]); // de stdin->stdout à stdin->source
      fork_exec_pipe(args+pipe_idx, pipe_fds[0], 1); // de stdin->stdout à target->stdout

      wait(NULL);
      wait(NULL);
    } 
    else {
      // pid clone le process en cours. Le child va executer, 
      // et le parent va continuer sa boucle.
      pid_t pid = fork();
      // il y a maintenant deux process qui sont à ce point du code.
      // si pid = 0, on est dans le nouveau process -> on execute
      if (pid == 0)
        // note : execvp recoit tous les arguments, y compris le nom de la commande. 
        // Donc args en entier.
        execvp(args[0], args);
      wait(NULL);
    }

  }

}

int main(int argc, char const *argv[])
{
  
  shell_loop();
  
  return 0;
}