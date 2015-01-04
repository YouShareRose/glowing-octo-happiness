/* 
 * 文件名称：stu_info_sys.sql
 * 功能描述：创建数据库和表，数据库名称为stu_info_sys，以及学生信息表student，教师信息表teacher，课程信息表course，成绩表score
 */
/* 创建数据库stu_info_sys */
CREATE DATABASE IF NOT EXISTS stu_info_sys DEFAULT CHARSET UTF8 COLLATE UTF8_GENERAL_CI;
/* 选择数据库stu_info_sys * */
USE stu_info_sys;

/* 创建学生信息表，学号为主键 */
CREATE TABLE student (
		stu_id VARCHAR(10) NOT NULL,
		stu_name VARCHAR(20) NOT NULL,
		stu_passwd VARCHAR(10) NOT NULL DEFAULT '123456',
		stu_gender ENUM('M','F') NOT NULL,
		stu_birth DATE NOT NULL,
		stu_depart VARCHAR(20) NOT NULL,
		stu_class VARCHAR(20) NOT NULL,
PRIMARY KEY (stu_id)
)ENGINE=innoDB DEFAULT CHARSET UTF8;

/* 创建教师信息表，教师ID为主键 */
CREATE TABLE teacher (
		tea_id VARCHAR(10) NOT NULL,
		tea_name VARCHAR(20) NOT NULL,
		tea_passwd VARCHAR(10) NOT NULL DEFAULT '123456',
		tea_gender ENUM('M','F') NOT NULL,
		tea_birth DATE NOT NULL,
		tea_depart VARCHAR(20) NOT NULL,
PRIMARY KEY (tea_id)
)ENGINE=innoDB DEFAULT CHARSET UTF8;

/* 创建课程信息表，课程编号为主键 */
CREATE TABLE course (
		crs_id VARCHAR(10) NOT NULL,
		crs_name VARCHAR(20) NOT NULL,
		crs_credit TINYINT NOT NULL,
		crs_hour SMALLINT NOT NULL,
		tea_id VARCHAR(10) NOT NULL,
PRIMARY KEY (crs_id),
FOREIGN KEY (tea_id) REFERENCES teacher(tea_id)
ON DELETE CASCADE
ON UPDATE CASCADE
)ENGINE=innoDB DEFAULT CHARSET UTF8;

/* 创建成绩表，学号和课程编号为联合主键 */
CREATE TABLE score (
		stu_id VARCHAR(10) NOT NULL,
		crs_id VARCHAR(10) NOT NULL,
		mark numeric(5,1) DEFAULT 0 NOT NULL,
		CHECK(mark BETWEEN 0.0 AND 100.0),
		CONSTRAINT markpk PRIMARY KEY (stu_id,crs_id),
		CONSTRAINT markfk1 FOREIGN KEY (stu_id) REFERENCES student(stu_id),
		CONSTRAINT markfk2 FOREIGN KEY (crs_id) REFERENCES course(crs_id)
)ENGINE=innoDB DEFAULT CHARSET UTF8;
