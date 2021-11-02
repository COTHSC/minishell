 #include "../../includes/minishell.h" 

int count_exported_vars(char **env)
 {
     int i;
     int c;

     i = -1;
     c = 0;
     while (env[++i])
     {
         if (env[i][0] == 'x')
             c++;
     }
     return (c);
 }

 char **ft_exported_vars(char **env, char select)
 {
     int i;
     int c;
     char **clean_env;

     i = -1;
     c = 0;
     clean_env = (char**)malloc(count_exported_vars(env) * sizeof(char*) + 1);
     while (env[++i])
     {
         if (env[i][0] == select)
         {
             clean_env[c] = &env[i][1];
             c++;
         }
     }
     clean_env[c] = NULL;
     return (clean_env);
 }
