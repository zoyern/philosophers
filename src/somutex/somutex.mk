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

SOMUTEX_DIR		=	somutex

SOMUTEX_HEADER	=	somutex.h
SOMUTEX_FILE		=	somutex.c 

SOMUTEX			=	$(addprefix $(SOMUTEX_DIR)/, $(SOMUTEX_FILE))
SOMUTEX_HEAD		=	$(addprefix $(SOMUTEX_DIR)/, $(SOMUTEX_HEADER))