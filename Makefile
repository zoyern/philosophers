# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zoyern <zoyern@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/19 16:01:12 by marvin            #+#    #+#              #
#    Updated: 2024/06/13 12:43:57 by zoyern           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

include build.mk

#❖═════Commandes══════❖
all : $(NAME)

clear :
	@clear
	@echo "42Paris : $(PROG_NAME)"
	@echo ""

clean : clear
	@rm -rf build/
	@echo "Clean   : *.o in build !"

fclean :
	@rm -f $(PROG_NAME)
	@rm -rf minilibx-linux
	@rm -rf build/includes/mlx.h
	@rm -rf libs
	@rm -rf build/obj/
	@echo "Clean   : ./$(PROG_NAME)"


val :
	@make re
	@clear
	valgrind --tool=helgrind ./$(PROG_NAME) 1 2000 20 20
	@echo ""

check : 
	@make re
	@clear
	funcheck -o ./$(PROG_NAME) $(ARGS)
	@echo ""

MLX_GIT = https://github.com/42Paris/minilibx-linux.git;

mlx :
	@git clone https://github.com/42Paris/minilibx-linux.git
	@make -C ./minilibx-linux

#❖═══Dependencies═══❖
dependencies: $(BUILD_INCLUDES)
	@mkdir -p $(LIBS_DIR)
	@for dep in $(DEPENDENCIES); do \
		name=$$(echo $$dep | cut -d ':' -f 1); \
		url=$$(echo $$dep | awk -F':' '{print substr($$0, index($$0, ":") + 1)}'); \
		if [ ! -d $(LIBS_DIR)/$$name ]; then \
			echo "Cloning $$name..."; \
			git clone $$url $(LIBS_DIR)/$$name; \
		else \
			echo "Pulling $$name..."; \
			(cd $(LIBS_DIR)/$$name && git pull -f); \
		fi; \
	done
	@$(eval LIBRARYS += $(foreach dep,$(DEPENDENCIES),$(LIBS_DIR)/$(firstword $(subst :, ,$(dep)))/$(BUILD_DIR)/$(firstword $(subst :, ,$(dep))).a))
	@$(eval LIBS_OBJ += $(foreach dep,$(DEPENDENCIES),$(LIBS_DIR)/$(firstword $(subst :, ,$(dep)))/$(BUILD_DIR)/obj))
	@$(eval LIBS_INCLUDES += $(foreach dep,$(DEPENDENCIES),$(LIBS_DIR)/$(firstword $(subst :, ,$(dep)))/$(BUILD_DIR)/includes))
	@$(eval LIBS_HEADER += $(foreach dep,$(DEPENDENCIES),$(LIBS_DIR)/$(firstword $(subst :, ,$(dep)))/$(BUILD_DIR)/includes/$(firstword $(subst :, ,$(dep))).h))
	@$(eval ALL_L_INCLUDES += $(foreach dep,$(DEPENDENCIES),$(LIBS_DIR)/$(firstword $(subst :, ,$(dep)))/$(BUILD_DIR)/includes/$(firstword $(subst :, ,$(dep)))))
	@cp $(LIBS_HEADER) $(BUILD_INCLUDES)
	@cp -r $(ALL_L_INCLUDES) $(BUILD_INCLUDES)

re: clean all clear 

.PHONY: all start clean fclean re val dependencies check