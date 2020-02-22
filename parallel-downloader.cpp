#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;


int main()
{
  //Store each line of the file temporary in line
  string line = "";

  //create fstream for file
  size_t counter = 0;
  std::ifstream file;
  file.open("./urls.txt");
  if(file.fail())
  {
    //Could not open the file
      exit(1);
  }

  pid_t pid;
    while(getline(file, line)) {
    pid = fork();
    counter++;
    if(pid == 0)
       {
         //We are in child process
         /* The command buffer */
         const string buffer= "/bin/wget";

         execlp(buffer.c_str(), "wget", line.c_str(), NULL);
       }
    else if(pid < 0){
      //An error has occurred
      exit(1);
    }

  }


  for(int i = 0; i < counter; i++) {
    //If we are in a parent process make it wait for the children
    if(pid > 0) {
      cout << counter <<endl;
      //We are in parent. Wait for children
      wait(NULL);

    }

  }
    return 0;
}
