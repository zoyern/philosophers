# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    exemple.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zoyern <zoyern@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/01 18:55:59 by marvin            #+#    #+#              #
#    Updated: 2024/06/12 23:16:59 by zoyern           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include exemple/map/map.mk

EXEMPLE_DIR		= $(CURDIR)/exemple

EXEMPLE_FILES	= main.c

EXEMPLE_FILES	+= $(MAP)

SRC_EXEMPLE	= $(addprefix $(EXEMPLE_DIR)/, $(EXEMPLE_FILES))
