OBJ_DIR=	./obj/
OBJ=		$(SRC:$(SRC_DIR)%.cpp=$(OBJ_DIR)%.o)

NAME_EXTENSION=	$(suffix $(NAME))

$(NAME):	$(OBJ)
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
		@$(ECHO) "$(WHITE)[$(YELLOW)RM$(WHITE)] Removed OBJs files\n$(CLEAR)"

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

.PHONY: all clean fclean re run install
