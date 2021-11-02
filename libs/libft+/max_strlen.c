#include "./libftp.h"

int	max_strlen(const char *s1, const char *s2)
{
	int len1;
	int len2;

	if (!s1)
		len1 = 0;
	else
		len1 = ft_strlen(s1);
	if (!s2)
		len2 = 0;
	else
		len2 = ft_strlen(s2);
	if (len1 >= len2)
		return (len1);
	else
		return (len2);
}
