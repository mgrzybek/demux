/**
 * Project: Demux: an open source task demultiplexing tool 
 * File name: dm.h
 * Description: The program is used to enqueue its input and process it thanks
 * to a user-defined command running into threads. It can be useful to launch
 * several mono-threaded workers to process a large number of elements :
 * - bzip2 / gzip a list of files
 * - use a shell script to process a list of files...
 * 
 * @author Mathieu Grzybek on 2011-12-18
 * @copyright 2011 Mathieu Grzybek. All rights reserved.
 * @version $Id: code-gpl-license.txt,v 1.2 2004/05/04 13:19:30 garry Exp $
 * 
 * @see The GNU Public License (GPL) version 3 or higher
 *
 * 
 * Demux is free software; you can redistribute it and/or modify 
 * it under the terms of the GNU General Public License as published by 
 * the Free Software Foundation; either version 3 of the License, or 
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful, but 
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
 * or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License 
 * for more details.
 * 
 * You should have received a copy of the GNU General Public License along 
 * with this program; if not, write to the Free Software Foundation, Inc., 
 * 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef DM_H
#define DM_H

#include <string>
#include <iostream>
#include <boost/thread.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/regex.hpp>

#include "elements_queue.h"
#include "worker.h"

/*
 * main
 *
 * dm's main function
 *
 * @arg argc	: the number of dm's arguments
 * @arg argv	: the arguments
 *
 * @return EXIT_SUCESS or EXIT_FAILURE
 */
int	main(int argc, char* const argv[]);

/*
 * usage
 *
 * Prints the command's usage
 */
void	usage();

#endif // DM_H

