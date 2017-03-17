OBJ_DIR=	${PWD}/obj/
OBJ=		$(SRC:$(SRC_DIR)%.cpp=$(OBJ_DIR)%.o)
OBJ_DIR_LIST=	$(DIR_LIST:$(SRC_DIR)%=$(OBJ_DIR)%)

NAME_EXTENSION=	$(suffix $(NAME))

$(NAME):	prepare_obj_dir $(OBJ)
ifeq ($(NAME_EXTENSION),.a)
		@$(RANLIB) $(NAME) $(OBJ) && \
		$(ECHO) "$(WHITE)[$(GREEN)OK$(WHITE)] Generated $(CYAN)"$(NAME)"\n$(CLEAR)" || \
		$(ECHO) "$(WHITE)[$(RED)KO$(WHITE)] Generated $(CYAN)"$(NAME)"\n$(CLEAR)"
else
		@$(CXX) $(OBJ) $(LDFLAGS) -o $(NAME) && \
		$(ECHO) "$(WHITE)[$(GREEN)OK$(WHITE)] Linked $(CYAN)"$(NAME)"\n$(CLEAR)" || \
		$(ECHO) "$(WHITE)[$(RED)KO$(WHITE)] Linked $(CYAN)"$(NAME)"\n$(CLEAR)"
endif

$(OBJ_DIR)%.o:	$(SRC_DIR)%.cpp
		@$(CXX) $(CXXFLAGS) -c -o $@ $< && \
		$(ECHO) "$(WHITE)[$(GREEN)OK$(WHITE)] Compiled "$<"\n$(CLEAR)" || \
		$(ECHO) "$(WHITE)[$(RED)KO$(WHITE)] Compiled "$<"\n$(CLEAR)"

all:		$(NAME)

infos:
		@$(ECHO) "$(CYAN)Compiler:\t\t$(CXX)\n"
		@$(ECHO) "Compilation Flags:\t$(CXXFLAGS)\n"
ifeq ($(NAME_EXTENSION),.a)
		@$(ECHO) "Library Generation:\t$(RANLIB)\n$(CLEAR)"
else
		@$(ECHO) "Link Flags:\t\t$(LDFLAGS)\n$(CLEAR)"
endif

clean:
		@$(RM) $(OBJ)
		@$(RM_DIR) $(OBJ_DIR)
		@$(ECHO) "$(WHITE)[$(YELLOW)RM$(WHITE)] Removed OBJs files and directory\n$(CLEAR)"

fclean:		clean
		@$(RM) $(NAME)
		@$(ECHO) "$(WHITE)[$(YELLOW)RM$(WHITE)] Removed $(CYAN)"$(NAME)"\n$(CLEAR)"

re:		fclean all

install:
ifeq ($(NAME_EXTENSION),)
		@$(CP) $(NAME) $(INSTALL_PATH) && \
		$(ECHO) "$(WHITE)[$(PURPLE)CP$(WHITE)] Installed $(CYAN)"$(NAME)"\n$(CLEAR)" || \
		$(ECHO) "$(WHITE)[$(PURPLE)CP$(WHITE)] Cannot install $(CYAN)"$(NAME)"\n$(CLEAR)"
else
		$(ECHO) "$(WHITE)[$(PURPLE)CP$(WHITE)] Not an executable, skipping ...\n$(CLEAR)"
endif

uninstall:
ifeq ($(NAME_EXTENSION),)
		@$(RM) $(INSTALL_PATH)/$(NAME)
		@$(ECHO) "$(WHITE)[$(RED)RM$(WHITE)] Uninstalled $(CYAN)"$(NAME)"\n$(CLEAR)"
else
		$(ECHO) "$(WHITE)[$(RED)RM$(WHITE)] Not an installed, skipping ...\n$(CLEAR)"
endif

run:
		./$(NAME)

mk_obj_dir=	$(if $(shell if [ ! -d $(1) ]; then echo "1"; fi),\
			$(MKDIR) $(1) && \
			$(ECHO) "$(WHITE)[$(PURPLE)MKDIR$(WHITE)] Created obj directory $(CYAN)"$(1)"\n$(CLEAR)" || \
			$(ECHO) "$(WHITE)[$(PURPLE)MKDIR$(WHITE)] Cannot create obj directory $(CYAN)"$(1)"\n$(CLEAR)"; \
		)

prepare_obj_dir:
		@$(foreach dir, $(OBJ_DIR_LIST), $(call mk_obj_dir,$(dir)))

.PHONY: all clean fclean re run install prepare_obj_dir
