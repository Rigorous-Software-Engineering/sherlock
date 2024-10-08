// PARAM: --set ana.activated[+] "'var_eq'"  --set ana.activated[+]
// "'symb_locks'"  --set ana.activated[+] "'region'"  --set kernel true --set
// nonstatic true --set exp.region-offsets true
#include <linux/module.h>
#include <linux/list.h>
#include <linux/mutex.h>
#include <linux/slab.h>

struct s {
  int datum;
  struct list_head list;
};

struct list_head slot[10];
struct mutex slots_mutex[10];

struct s *new(int x) {
  struct s *p = kmalloc(sizeof(struct s), GFP_KERNEL);
  p->datum = x;
  INIT_LIST_HEAD(&p->list);
  return p;
}

void t1(int i) {
  struct s *p;

  p = new (1);
  mutex_lock(&slots_mutex[i]);
  list_add(&p->list, &slot[i]);
  p = new (2);
  list_add(&p->list, &slot[i]);
  mutex_unlock(&slots_mutex[i]);
}

void t2(int j) {
  struct s *pos;
  int j;

  mutex_lock(&slots_mutex[j]);
  list_for_each_entry(pos, &slot[j], list) {
    pos->datum++; // NORACE!
  }
  mutex_unlock(&slots_mutex[j]);
}
