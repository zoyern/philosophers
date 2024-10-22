# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    sotask.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marvin <marvin@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/21 14:50:36 by marvin            #+#    #+#              #
#    Updated: 2024/10/21 14:50:36 by marvin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SOTASK_DIR		=	sotask

SOTASK_HEADER		=	sotask.h
SOTASK_FILE		=	sotask.c sotask_add.c  sotask_remove.c 

SOTASK			=	$(addprefix $(SOTASK_DIR)/, $(SOTASK_FILE))
SOTASK_HEAD		=	$(addprefix $(SOTASK_DIR)/, $(SOTASK_HEADER))