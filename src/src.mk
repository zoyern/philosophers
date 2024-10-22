# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    src.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: almounib <almounib@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/01 18:55:59 by marvin            #+#    #+#              #
#    Updated: 2024/05/16 14:38:34 by almounib         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include $(CURDIR)/src/sotask/sotask.mk

SRC_DIR		=	$(CURDIR)/src

LIB_HEADER	=	$(addprefix $(SRC_DIR)/, sothread.h)
SRC_HEADER	=	sothread_t.h all.h
SRC_FILES	=	sothread.c

DIR			+= $(SOTASK_DIR)

SRC_HEADER	+= $(SOTASK_HEAD)

SRC_FILES	+= $(SOTASK)

HEADERS		=	$(addprefix $(SRC_DIR)/, $(SRC_HEADER))
SRC			=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))
FOLDERS		=	$(addprefix $(SRC_DIR)/, $(DIR))
FOLDERS		+=	$(SRC_DIR)