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

include src/gears/gears.mk
include src/timers/timers.mk

SRC_DIR		=	$(CURDIR)/src

LIB_HEADER	=	$(addprefix $(SRC_DIR)/, sotime.h)
SRC_HEADER	=	sotime_t.h all.h
SRC_FILES	=	sotime.c

DIR			+= $(GEARS_DIR)
DIR			+= $(TIMERS_DIR)

SRC_HEADER	+= $(GEARS_HEAD)
SRC_HEADER	+= $(TIMERS_HEAD)

SRC_FILES	+= $(GEARS)
SRC_FILES	+= $(TIMERS)

HEADERS		=	$(addprefix $(SRC_DIR)/, $(SRC_HEADER))
SRC			=	$(addprefix $(SRC_DIR)/, $(SRC_FILES))
FOLDERS		=	$(addprefix $(SRC_DIR)/, $(DIR))
FOLDERS		+=	$(SRC_DIR)