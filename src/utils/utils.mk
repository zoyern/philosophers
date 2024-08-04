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

UTILS_DIR		=	utils

UTILS_HEADER	=	utils.h
UTILS_FILE		=	utils.c utils_monitor.c utils_thread.c utils_mutex.c utils_print.c

UTILS			=	$(addprefix $(UTILS_DIR)/, $(UTILS_FILE))
UTILS_HEAD		=	$(addprefix $(UTILS_DIR)/, $(UTILS_HEADER))