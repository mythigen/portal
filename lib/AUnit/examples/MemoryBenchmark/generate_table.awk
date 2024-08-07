#!/usr/bin/gawk -f
#
# Usage: generate_table.sh < ${board}.txt
#
# Takes the file generated by collect.sh and generates an ASCII
# table that can be inserted into the README.md.

BEGIN {
  labels[0] = "Baseline"
  labels[1] = "AUnit Single Test"
  labels[2] = "AUnit Single Test Verbose"
  record_index = 0
}
{
  u[record_index]["flash"] = $2
  u[record_index]["ram"] = $4
  record_index++
}
END {
  NUM_ENTRIES = record_index

  base_flash = u[0]["flash"]
  base_ram = u[0]["ram"]
  for (i = 0; i < NUM_ENTRIES; i++) {
    if (u[i]["flash"] == -1) {
      u[i]["d_flash"] = -1
      u[i]["d_ram"] = -1
    } else {
      u[i]["d_flash"] = u[i]["flash"] - base_flash
      u[i]["d_ram"] = u[i]["ram"]- base_ram
    }
  }

  printf(\
    "+---------------------------------------------------------------------+\n")
  printf(\
    "| Functionality                          |  flash/  ram |       delta |\n")
  for (i = 0; i < NUM_ENTRIES; i++) {
    if (labels[i] ~ /^Baseline/ \
        || labels[i] ~ /^AUnit Single Test$/ \
    ) {
      printf(\
        "|----------------------------------------+--------------+-------------|\n")
    }
    printf("| %-38s | %6d/%5d | %5d/%5d |\n",
        labels[i], u[i]["flash"], u[i]["ram"], u[i]["d_flash"], u[i]["d_ram"])
  }
  printf(\
    "+---------------------------------------------------------------------+\n")
}
