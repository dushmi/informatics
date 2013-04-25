/**
 * Copyright (C) 2012 Bogdan-Cristian Tătăroiu
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int pids[2], pipes[2][2], i;

    // Program expects two other executables as parameters
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <executable> <executable>\n",
                argv[0]);
        exit(EXIT_FAILURE);
    }

    // Create a couple of pipes
    for (i = 0; i < 2; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }

    // Fork the two child processes and execute
    for (i = 0; i < 2; i++) {
        pids[i] = fork();
        if (pids[i] == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }
        if (pids[i] == 0) {
            // The other program's output becomes this program's stdin
            if (dup2(pipes[i ^ 1][0], 0 /* stdin */) == -1) {
                perror("dup2");
                exit(EXIT_FAILURE);
            }
            // This program's stdout becomes the other program's input
            if (dup2(pipes[i][1], 1 /* stdout */) == -1) {
                perror("dup2");
                exit(EXIT_FAILURE);
            }

            // Execute the program
            execve(argv[i + 1], NULL, NULL);
            perror("execve");       // execve() only returns on error
            exit(EXIT_FAILURE);
        } else {
            printf("Program %s started with pid %d\n",
                   argv[i + 1], pids[i]);
        }
    }

    // Close pipes in main program, it does not need them
    for (i = 0; i < 2; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    int running;
    // Wait for running processes to terminate
    for (running = 2; running > 0; ) {
        int status;
        pid_t pid = waitpid(-1, &status, 0);
        if (pid == -1) {
            perror("waitpid");
        }
        if (WIFEXITED(status)) {
            printf("%d exited with status %d\n", pid, WEXITSTATUS(status));
            running -= 1;
        } else if (WIFSIGNALED(status)) {
            printf("%d killed by signal %d\n", pid, WTERMSIG(status));
            running -= 1;
        }
    }

    exit(EXIT_SUCCESS);
}
