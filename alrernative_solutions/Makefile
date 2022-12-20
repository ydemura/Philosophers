NAME = philo_new
SRCS = philo/main.c $(SRCS_FOLDER)

SRCS_FOLDER = philo/form_philo_data.c philo/input_in_structs.c philo/loop_thread.c philo/main_thread.c philo/utilities.c

OBJ = $(SRCS:.c=.o)
FLAGS = -Wall -Wextra  -g 
# -Werror
#-g -fsanitize=thread      (CHECKS FOR DATA RACES)
#-g -fsanitize=address
HEADER = philo
CC = clang

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(OBJ) -o $(NAME)

%.o: %.c $(HEADER)
	$(CC) $(FLAGS) -c -o $@ $< -I $(HEADER)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re:
	$(MAKE) fclean
	$(MAKE) all

.PHONY: all clean fclean re
