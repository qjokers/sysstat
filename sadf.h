/*
 * sadf: System activity data formatter
 * (C) 1999-2015 by Sebastien Godard (sysstat <at> orange.fr)
 */

#ifndef _SADF_H
#define _SADF_H

#include "sa.h"

/* DTD version for XML output */
#define XML_DTD_VERSION	"3.1"

/* Various constants */
#define DO_SAVE		0
#define DO_RESTORE	1

#define IGNORE_NOTHING		0
#define IGNORE_RESTART		1
#define DONT_READ_VOLATILE	2
#define IGNORE_COMMENT		4

/*
 ***************************************************************************
 * Output format identification values.
 ***************************************************************************
 */

/* Number of output formats */
#define NR_FMT	6

/* Output formats */
#define F_DB_OUTPUT	1
#define F_HEADER_OUTPUT	2
#define F_PPC_OUTPUT	3
#define F_XML_OUTPUT	4
#define F_JSON_OUTPUT	5
#define F_CONV_OUTPUT	6

/* Format options */

/*
 * Indicate that all statistics data for one activity should be displayed before
 * displaying stats for next activity. This is what sar does in its report.
 * Example: If stats for activities A and B at time t and t' have been collected,
 * setting AO_GROUPED_STATS for a format will result in the following output:
 * stats for activity A at t
 * stats for activity A at t'
 * stats for activity B at t
 * stats for activity B at t'
 * Without this option, output would be:
 * stats for activity A at t
 * stats for activity B at t
 * stats for activity A at t'
 * stats for activity B at t'
 */
#define FO_GROUPED_STATS	0x01

/*
 * Indicate that output should stop after the header is displayed.
 */
#define FO_HEADER_ONLY		0x02

/*
 * Indicate that a true sysstat activity file but with a bad
 * format should not yield an error message.
 */
#define FO_BAD_FILE_FORMAT	0x04

/*
 * Indicate that timestamp can be displayed in local time instead of UTC
 * if option -T or -t has been used.
 */
#define FO_LOCAL_TIME		0x08

/*
 * Indicate that all activities will be displayed horizontally
 * if option -h is used.
 */
#define FO_HORIZONTALLY		0x10

/*
 * Indicate that the timestamp can be displayed in seconds since the epoch
 * if option -U has been used.
 */
#define FO_SEC_EPOCH		0x20

/*
 * Indicate that the list of fields should be displayed before the first
 * line of statistics.
 */
#define FO_FIELD_LIST		0x40

/*
 * Indicate that flag AO_CLOSE_MARKUP (set for activities that need it)
 * should be taken into account for this output format.
 */
#define FO_TEST_MARKUP		0x80

#define DISPLAY_GROUPED_STATS(m)	(((m) & FO_GROUPED_STATS)	== FO_GROUPED_STATS)
#define ACCEPT_HEADER_ONLY(m)		(((m) & FO_HEADER_ONLY)		== FO_HEADER_ONLY)
#define ACCEPT_BAD_FILE_FORMAT(m)	(((m) & FO_BAD_FILE_FORMAT)	== FO_BAD_FILE_FORMAT)
#define ACCEPT_LOCAL_TIME(m)		(((m) & FO_LOCAL_TIME)		== FO_LOCAL_TIME)
#define ACCEPT_HORIZONTALLY(m)		(((m) & FO_HORIZONTALLY)	== FO_HORIZONTALLY)
#define ACCEPT_SEC_EPOCH(m)		(((m) & FO_SEC_EPOCH)		== FO_SEC_EPOCH)
#define DISPLAY_FIELD_LIST(m)		(((m) & FO_FIELD_LIST)		== FO_FIELD_LIST)
#define TEST_MARKUP(m)			(((m) & FO_TEST_MARKUP)		== FO_TEST_MARKUP)

/*
 ***************************************************************************
 * Various function prototypes
 ***************************************************************************
 */

void convert_file
	(char [], struct activity *[]);
void xprintf
	(int, const char *, ...);
void xprintf0
	(int, const char *, ...);

/*
 * Prototypes used to display restart messages
 */
__printf_funct_t print_db_restart
	(int *, int, char *, char *, int, struct file_header *, unsigned int);
__printf_funct_t print_ppc_restart
	(int *, int, char *, char *, int, struct file_header *, unsigned int);
__printf_funct_t print_xml_restart
	(int *, int, char *, char *, int, struct file_header *, unsigned int);
__printf_funct_t print_json_restart
	(int *, int, char *, char *, int, struct file_header *, unsigned int);
__printf_funct_t print_sar_restart
	(int *, int, char *, char *, int, struct file_header *, unsigned int);

/*
 * Prototypes used to display comments
 */
__printf_funct_t print_db_comment
	(int *, int, char *, char *, int, char *, struct file_header *);
__printf_funct_t print_ppc_comment
	(int *, int, char *, char *, int, char *, struct file_header *);
__printf_funct_t print_xml_comment
	(int *, int, char *, char *, int, char *, struct file_header *);
__printf_funct_t print_json_comment
	(int *, int, char *, char *, int, char *, struct file_header *);
__printf_funct_t print_sar_comment
	(int *, int, char *, char *, int, char *, struct file_header *);

/*
 * Prototypes used to display the statistics part of the report
 */
__printf_funct_t print_xml_statistics
	(int *, int);
__printf_funct_t print_json_statistics
	(int *, int);

/*
 * Prototypes used to display the timestamp part of the report
 */
__tm_funct_t print_db_timestamp
	(int *, int, char *, char *, unsigned long long, struct file_header *, unsigned int);
__tm_funct_t print_ppc_timestamp
	(int *, int, char *, char *, unsigned long long, struct file_header *, unsigned int);
__tm_funct_t print_xml_timestamp
	(int *, int, char *, char *, unsigned long long, struct file_header *, unsigned int);
__tm_funct_t print_json_timestamp
	(int *, int, char *, char *, unsigned long long, struct file_header *, unsigned int);

/*
 * Prototypes used to display the report header
 */
__printf_funct_t print_xml_header
	(int *, int, char *, struct file_magic *, struct file_header *,
	 __nr_t, struct activity * [], unsigned int []);
__printf_funct_t print_json_header
	(int *, int, char *, struct file_magic *, struct file_header *,
	 __nr_t, struct activity * [], unsigned int []);
__printf_funct_t print_hdr_header
	(int *, int, char *, struct file_magic *, struct file_header *,
	 __nr_t, struct activity * [], unsigned int []);

#endif  /* _SADF_H */
