#include "uls.h"

/*
 * Функция заполняет пользовательстуку структуру - аналог stat t_lstat
 * различными данными. При реализации новых флагов можно добавлять данные по
 * необходимости.
 */

t_lstat *mx_lstat_fill(struct stat buf, char *argv, int *flags, bool r) {
    t_lstat *res = malloc(sizeof(t_lstat));

    res->path = mx_strdup(argv);
    res->name = mx_get_name(argv, flags, buf, r);
    res->mode = mx_get_permission(buf.st_mode, res->path);
    res->nlink = buf.st_nlink;
    res->size_b = mx_get_size(buf);
    res->plink = mx_get_plink(argv, buf.st_size, res->mode[0]);
    res->own_name = mx_get_owner(buf.st_uid);
    res->group = mx_get_group(buf.st_gid);
    res->mtime = mx_get_mtime(buf, flags);
    res->total = mx_get_total(buf);
    res->st_size = buf.st_size;
    res->st_time = buf.st_mtimespec.tv_sec;
    res->st_time_nsec = buf.st_mtimespec.tv_nsec;
    if (flags[mx_get_char_index(FLAGS, 'u')]) {
        res->st_time = buf.st_atimespec.tv_sec;
        res->st_time_nsec = buf.st_atimespec.tv_nsec;
    }
    res->next = NULL;
    return res;
}
