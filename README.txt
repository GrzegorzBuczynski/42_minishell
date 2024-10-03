
// ------------------------------TO DO------------------------------
// 1) Validate input (quotes etc)
// 2) momory leaks
// 3) signals


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


parsing
1. exec_cmd parsing should be continued after redirection
2. after redirection start string without space
3. read quoted blocks as one string

execution 
1. stop opening files on first fail and return exit code 1
2. po wszytkich cmd exec odpalony
3. redirection dodawane do listy, jesli istniala nastepna dodaj jako subcmd, aktualizuj current i jesli current istnial dodaj sub.
na konic gdy jest pipe do sub dodaj exec_cmd.


