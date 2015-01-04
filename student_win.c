/* 
 * 文件名称：student_win.c
 * 功能描述：构建学生查询GUI界面，处理学生用户的各种查询操作
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gtk/gtk.h>
#include <glade/glade.h>

#define _N(str) g_locale_to_utf8(str, -1, NULL,NULL,NULL)

enum
{
    CRS_ID = 0,
    CRS_NAME,
    CRS_CREDIT,
    CRS_HOUR,
    MARK,
    STU_COLUM_NUM
};
extern Table stu_res_tab;

int show_student_window()
{
		GladeXML *StudentWinXML;
		GtkWidget *student_window, *exit_button;
		GtkWidget *treeview;      /*树视图*/
		GtkTreeIter iter;           /*迭代器*/
		GtkCellRenderer* renderer;  /*渲染器*/
		GtkTreeModel *store;      /*树模式*/
		char *sqlresult;
		MYSQL_ROW row;
		unsigned int i=0;
		
		gtk_init(&argc,&argv);
		StudentWinXML = glade_xml_new("ui/student_win.glade", NULL, NULL);
		student_window = glade_xml_get_widget(StudentWinXML, "window1");
		glade_xml_signal_autoconnect(StudentWinXML);
		treeview = glade_xml_get_widget(StudentWinXML, "treeview");
		/*定义渲染器，定义视图中的列，设置各列的数据均为text*/
		renderer = gtk_cell_renderer_text_new();
		gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, _N(" 课程编号 "), renderer, "text", CRS_ID, NULL);
		gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, _N(" 课程名称 "), renderer, "text", CRS_NAME, NULL);
		gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, _N(" 学  分 "), renderer, "text", CRS_CREDIT, NULL);
		gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, _N(" 学  时 "), renderer, "text", CRS_HOUR, NULL);
		gtk_tree_view_insert_column_with_attributes(GTK_TREE_VIEW(treeview), -1, _N(" 成  绩 "), renderer, "text", MARK, NULL);
		/*设置树模式中各列的数据类型*/
		store = GTK_TREE_MODEL(gtk_list_store_new(STU_COLUM_NUM,G_TYPE_STRING,G_TYPE_STRING,G_TYPE_UINT,G_TYPE_UINT,G_TYPE_FLOAT));
		gtk_tree_view_set_model(GTK_TREE_VIEW(treeview), store);
		/*向模式中插入数据*/
		for(i=0; i<stu_res_tab.row; i++)
		{
			row = mysql_fetch_row(stu_res_tab.res)
			gtk_list_store_append(GTK_LIST_STORE(store), &iter);  /*获取插入的位置*/
			gtk_list_store_set(GTK_LIST_STORE(store),&iter,CRS_ID,row[CRS_ID],CRS_NAME,row[CRS_NAME],CRS_CREDIT,row[CRS_CREDIT],CRS_HOUR,row[CRS_HOUR],MARK,row[MARK],-1);
		}
		g_object_unref(store);
		/*为界面添加信号*/
		exit_button = glade_xml_get_widget(StudentWinXML, "exit_button");
		g_signal_connect(G_OBJECT(exit_button), "clicked", G_CALLBACK(gtk_main_quit),student_window);
		g_signal_connect(G_OBJECT(student_window),"destroy",G_CALLBACK(gtk_main_quit),student_window);
		gtk_widget_show_all(student_window);
		gtk_main();
		return 0;
}
