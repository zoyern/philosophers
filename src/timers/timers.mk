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

TIMERS_DIR		=	timers

TIMERS_HEADER	=	timers.h
TIMERS_FILE		=	timers.c

TIMERS			=	$(addprefix $(TIMERS_DIR)/, $(TIMERS_FILE))
TIMERS_HEAD		=	$(addprefix $(TIMERS_DIR)/, $(TIMERS_HEADER))