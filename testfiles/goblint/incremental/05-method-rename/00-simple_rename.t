Run Goblint on initial program version

  $ goblint --conf 00-simple_rename.json --enable incremental.save 00-simple_rename.c > /dev/null 2>&1

Apply patch

  $ chmod +w 00-simple_rename.c
  $ patch -b <00-simple_rename.patch
  patching file 00-simple_rename.c

Run Goblint incrementally on new program version and check the change detection result

  $ goblint --conf 00-simple_rename.json --enable incremental.load 00-simple_rename.c | grep 'change_info' | sed -r 's/^change_info = \{ unchanged = [[:digit:]]+; (.*) \}$/\1/'
  changed = 0 (with unchangedHeader = 0); added = 0; removed = 0
