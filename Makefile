VM_NAME = corewar

HEADERS =	op \
			vm \
			structures \
			encurse

INCDIR = ./includes
VMSRCDIR = ./vm_sources
HFILES = $(patsubst %, $(INCDIR)/%.h, $(HEADERS))

VMCMDSRCDIR = commands
VMCMDFNAMES = 	proc_invalid \
				proc_live \
				proc_load \
				proc_store \
				proc_zjmp \
				proc_fork

VMCCMDFILES = $(patsubst %, $(VMSRCDIR)/$(VMCMDSRCDIR)/%.c, $(VMCMDFNAMES))
VMOCMDFILES = $(patsubst %, $(ODIR)/$(VMCMDSRCDIR)/%.o, $(VMCMDFNAMES))

VMFILENAMES =	main \
				pre \
				errors \
				globals \
				player_reading \
				player_parsing \
				print_tools \
				process_tools \
				field_tools \
				commands \
				list_proc \
				main_pic

VMCFILES = $(patsubst %, $(VMSRCDIR)/%.c, $(VMFILENAMES)) $(VMCCMDFILES)
VMOFILES = $(patsubst %, $(ODIR)/%.o, $(VMFILENAMES)) $(VMOCMDFILES)

LIBDIR = ./libft
LIBFT = $(LIBDIR)/libft.a
FLAGS = #-Wall -Wextra -Werror
LIBINCDIR = $(LIBDIR)/includes

ODIR = ./obj

BLACK = '\033[0;30m'
RED = '\033[0;31m'
GREEN = '\033[0;32m'
BROWN = '\033[0;33m'
BLUE = '\033[0;34m'
PURPLE = '\033[0;35m'
CYAN = '\033[0;36m'
LGRAY = '\033[0;37m'
DGRAY = '\033[1;30m'
LRED = '\033[1;31m'
LGREEN = '\033[1;32m'
YELLOW = '\033[1;33m'
LBLUE = '\033[1;34m'
PINK = '\033[1;35m'
LCYAN = '\033[1;36m'
WHITE = '\033[1;37m'
NC = '\033[0m' # No Color

all: $(VM_NAME)

$(VM_NAME): $(ODIR) $(HFILES) $(VMOFILES)
	@echo ${CYAN}[Compiling the $(VM_NAME) executable]${NC}
	gcc $(FLAGS) $(VMOFILES) $(LIBFT) -o $(VM_NAME) -lncurses
	@echo ${GREEN}"[========| $(VM_NAME) is up to date. |========]"${NC}

$(ODIR)/%.o: $(VMSRCDIR)/%.c $(HFILES) $(LIBFT)
	gcc $(FLAGS) -o $@ -c $< -I$(INCDIR) -I$(LIBINCDIR) 


$(ODIR):
	@mkdir -p $(ODIR)
	@mkdir -p $(ODIR)/$(VMCMDSRCDIR)

$(LIBFT):
	@make -C $(LIBDIR)

clean:
	@echo ${RED}[Removing $(VM_NAME) *.o files]${NC}
	@/bin/rm -rf $(ODIR)
	@make clean -C ./libft
	
fclean: clean
	@echo ${RED}[Removing executable $(VM_NAME) file]${NC}
	@/bin/rm -f $(VM_NAME)
	@make fclean -C ./libft

re: fclean all
