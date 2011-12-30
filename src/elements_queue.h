/**
 * Project: Demux: an open source task demultiplexing tool 
 * File name: elements_queue.h
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

#ifndef ELEMENTS_QUEUE_H
#define ELEMENTS_QUEUE_H

#include <queue>
#include <string>
#include <boost/thread/mutex.hpp>

class	Elements_Queue {
public:
	/*
	 * Constructor
	 */
	Elements_Queue();

	/*
	 * Destructor
	 */
	~Elements_Queue();

	/*
	 * pop
	 *
	 * Pops the queue
	 *
	 * As the result string does no longer belong to the queue
	 * please do not forget to delete it.
	 *
	 * @return the poped string
	 */
	std::string*	pop();

	/*
	 * push
	 *
	 * Pushes a string into the queue
	 *
	 * @arg the string to push
	 */
	void		push(const char* element);

private:
	// Uesd to make the methods thead-safe
	boost::mutex		mutex;
	// The queue containing the data
	std::queue<std::string>	queue;
};

#endif // ELEMENTS_QUEUE_H

