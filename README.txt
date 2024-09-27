
// ------------------------------TO DO------------------------------
// 1) Validate input (quotes etc)
// 2) momory leaks
// 3) exit codes
// 4) move opening files to parsing
// 5) change commands to list


minishell_free.c // do usuniecia ff_putline_fd
build custom malloc that add new pointers to tracker linked list. 
// take minishell->line as input

git lens
github pull request

Set up your git.hooks pre-push with set_up_hooks.sh:
1) cd hooks
2) chomd 777 set_up_gt_hooks.sh
3) ./set_up_hooks.sh
4) Congratulation, you set up your proj!


parsing should be continued after redirection
[0m[0;33mTest  59: ❌[38;5;244m echo hi < ./test_files/infile bye bye 
[0mmini output = ()
bash output = (hi bye bye)
mini exit code = 1
bash exit code = 0
mini error = ( ye)
bash error = ()