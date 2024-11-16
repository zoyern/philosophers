# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    fork.mk                                            :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/07 20:23:13 by marvin            #+#    #+#              #
#    Updated: 2024/04/07 20:23:13 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOSYNC_DIR		=	sosync

SOSYNC_HEADER	=	sosync.h
SOSYNC_FILE		=	sosync.c sosync_2.c sosync_3.c sosync_4.c 

SOSYNC			=	$(addprefix $(SOSYNC_DIR)/, $(SOSYNC_FILE))
SOSYNC_HEAD		=	$(addprefix $(SOSYNC_DIR)/, $(SOSYNC_HEADER))