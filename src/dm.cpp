/**
 * Project: Demux: an open source task demultiplexing tool 
 * File name: dm.cpp
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

#include "dm.h"

//////////////////////////////////////////////////////////////////////////////

/*
 * main
 *
 * - Do I have enough arguments?
 * - Is the number of threads a number?
 * - Is this number greater or equal to 2?
 * - Push the elements into the queue according to the input's nature
 * - Launch the threaded workers
 * - Wait them and exit
 */
int	main(int argc, char* const argv[]) {
	std::string		cmd_tool;
	std::string		line;

	int			thr_number;
	int			count;

	Elements_Queue		elements;

	boost::thread_group	running_workers;
	boost::mutex		io_mutex;

	if ( argc < 4 ) {
		usage();
		return EXIT_FAILURE;
	}

	cmd_tool = argv[1];

	try {
		thr_number = boost::lexical_cast<int>(argv[2]);
	} catch (std::exception e) {
		std::cerr << "thr_number must be an integer" << std::endl;
		return EXIT_FAILURE;
	}

	if ( thr_number < 2 ) {
		std::cerr << "n_threads must be higher or equal to 2" << std::endl;
		return EXIT_FAILURE;
	}

	if ( argc == 4 and strcmp(argv[3],"-") == 0 ) {
		while ( getline(std::cin,line) )
			if ( not line.empty() )
				elements.push(line.c_str());
	
	} else 
		for ( count = 3 ; count < argc ; count++ )
			elements.push(argv[count]);

	for ( count = 1 ; count <= thr_number ; count++ ) {
		Worker	w(&io_mutex, &cmd_tool, &elements);
		running_workers.create_thread(boost::bind(&Worker::process, &w));
	}

	running_workers.join_all();
	
	return EXIT_SUCCESS;
}

//////////////////////////////////////////////////////////////////////////////

/*
 * usage
 *
 * Prints the usage message
 */
void	usage() {
	std::cout << "Usage:" << std::endl;
	std::cout << "dm <command> <n_threads> (<element1> [<element2> ... <elementN>]) || -" << std::endl;
	std::cout << "\t<command>	: the script to fork" << std::endl;
	std::cout << "\t<n_threads>	: the number of parallel workers to launch (>= 2)" << std::endl;
	std::cout << "\t<elementN>	: the arguments for the command" << std::endl;
	std::cout << "\t-		: get the elements from the standard input" << std::endl;
}

