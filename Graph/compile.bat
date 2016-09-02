@echo off
cls
cl /LD list.c
cl /LD graph.c list.lib
cl main_list.c list.lib
cl main_graph.c graph.lib list.lib
