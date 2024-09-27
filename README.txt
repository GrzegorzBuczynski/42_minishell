
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
check artefact
[0m[0;33mTest  59: ❌[38;5;244m echo hi < ./test_files/infile bye bye 
[0mmini output = ()
bash output = (hi bye bye)
mini exit code = 1
bash exit code = 0
mini error = ( ye)
bash error = ()

parsing
1. exec_cmd parsing should be continued after redirection
2. after redirection start string without space
3. read quoted blocks as one string

execution 
1. stop opening files on first fail and return exit code 1
2. po wszytkich cmd exec odpalony
3. redirection dodawane do listy, jesli istniala nastepna dodaj jako subcmd, aktualizuj current i jesli current istnial dodaj sub.
na konic gdy jest pipe do sub dodaj exec_cmd.

char **ps;
t_cmd *cmd;

ps = &input;
str = get_string(ps)
if (!is redirect(str))
	exec_cmd = append_argv(str);
else if (is_redirect(str))
	red_cmd = parse_redirect(ps, exec_cmd)
else if (is_pipe)
{
	if (red_cmd)
		cmd = red_cmd
	else
		cmd = exec_cmd
	minishell->commands[i] = cmd;
	minishell->number_of_commands++;
}


