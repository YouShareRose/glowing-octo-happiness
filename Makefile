/*
* 文件名称：Makefile
 * 功能描述：使用Make管理、编译工程
*/
CC=gcc
GTK_FLAGS=`pkg-config --libs --cflags libglade-2.0 gtk+-2.0`
SQL_FLAGS="-lmysqlclient -I/usr/local/mysql/include/mysql/"

stu_info_sys : main.o student_win.o teacher_win.o admin_win.o exec_sql.o
		$(CC) -o stu_info_sys main.o student_win.o teacher_win.o admin_win.o exec_sql.o $(GTK_FLAGS) $(SQL_FLAGS) 
	
main.o: main.c
		$(CC) -o main.o $(GTK_FLAGS) main.c
	
student_win.o: student_win.c
		$(CC) -o student_win.o $(GTK_FLAGS) $(SQL_FLAGS) student_win.c

teacher_win.o: teacher_win.c
		$(CC) -o teacher_win.o $(GTK_FLAGS) $(SQL_FLAGS) teacher_win.c

admin_win.o: admin_win.c
		$(CC) -o admin_win.o $(GTK_FLAGS) $(SQL_FLAGS) admin_win.c

exec_sql.o: exec_sql.c
		$(CC) -o exec_sql.o $(SQL_FLAGS) exec_sql.c
