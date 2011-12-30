#
# Project: Demux: an open source task demultiplexing tool 
# File name: CMakeLists.txt
# Description: The program is used to enqueue its input and process it thanks
# to a user-defined command running into threads. It can be useful to launch
# several mono-threaded workers to process a large number of elements :
# - bzip2 / gzip a list of files
# - use a shell script to process a list of files...
# 
# @author Mathieu Grzybek on 2011-12-18
# @copyright 2011 Mathieu Grzybek. All rights reserved.
# @version $Id: code-gpl-license.txt,v 1.2 2004/05/04 13:19:30 garry Exp $
# 
# @see The GNU Public License (GPL) version 3 or higher
#
# 
# Demux is free software; you can redistribute it and/or modify 
# it under the terms of the GNU General Public License as published by 
# the Free Software Foundation; either version 3 of the License, or 
# (at your option) any later version.
# 
# This program is distributed in the hope that it will be useful, but 
# WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY 
# or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License 
# for more details.
# 
# You should have received a copy of the GNU General Public License along 
# with this program; if not, write to the Free Software Foundation, Inc., 
# 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
#

cmake_minimum_required(VERSION 2.8)

project(dm)
add_subdirectory(src)

set(CMAKE_CXX_FLAGS_RELEASE)

add_definitions(-Wall -g -O2)

add_executable(dm
	src/dm.cpp
	src/worker.cpp
	src/elements_queue.cpp

	src/dm.h
	src/worker.h
	src/elements_queue.h
)

link_directories (
	/opt/local/lib
	/usr/local/lib
	/usr/lib
	/usr/share/lib
)

include_directories(
	/opt/local/include
	/usr/local/include
	/usr/include
	/usr/share/include
)

#
# Mac OS X
#
IF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
target_link_libraries(dm
	/opt/local/lib/libboost_thread-mt.a
	/opt/local/lib/libboost_regex.a
)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")

#
# GNU / Linux
#
IF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
target_link_libraries(dm
	pthread
	/usr/lib/libboost_thread.a
	/usr/lib/libboost_regex.a
)
ENDIF(${CMAKE_SYSTEM_NAME} MATCHES "Linux")

