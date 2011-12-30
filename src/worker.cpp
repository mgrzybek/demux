/**
 * Project: Demux: an open source task demultiplexing tool 
 * File name: worker.cpp
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

#include "worker.h"

/*
 * Constructor
 */
Worker::Worker(boost::mutex* mutex, const std::string* cmd, Elements_Queue* queue) {
	this->cmd	= cmd->c_str();
	this->queue	= queue;
	this->io_mutex	= mutex;
}

/*
 * Destructor
 */
Worker::~Worker() {
}

/*
 * process
 *
 * - Pops the queue
 * - Creates the command line (command name + poped argument)
 * - Prints the command line to stdout
 * - Run it using popen (thread-safe)
 * - Clear everything
 * - Pops the queue again
 */
bool	Worker::process() {
	std::string*	element;
	std::string	cmd_line;
	std::string	cmd = this->cmd.c_str();

	element = this->queue->pop();

	while ( element != NULL ) {
		cmd_line = cmd.c_str();
		cmd_line += " ";
		cmd_line += element->c_str();

		this->io_mutex->lock();
		std::cout << cmd_line << std::endl;
		this->io_mutex->unlock();

		FILE* stream = popen(cmd_line.c_str(), "r");
		pclose(stream);

		cmd_line.clear();
		element->clear();
		delete element;
		element = this->queue->pop();
	}

	return true;
}

