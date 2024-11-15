# so
just so a solong lib



if (!work && )

typedef struct s_fork { // libre
	int		work; // 0
	int		locked; // 0
	int		death; // 0
} t_fork;

typedef struct s_fork { // en cours
	int		work; // 1
	int		locked; // 1
	int		death; // 0
} t_fork;

typedef struct s_fork { // locked
	int		work; // 0
	int		locked; // 1
	int		death; // 0
} t_fork;

typedef struct s_fork { //mort
	int		work; // 0
	int		locked; // 0
	int		death; // 1 ou - 1
} t_fork;&

typedef struct s_mutex  // fork
{
	int				*locked = 0; // set to 1 mutex off
	int				*use = 0; // + 1 chaque eat
	long			*last = get_millis(); // set at starting 
	long			*starting = get_millis(); //starting
	t_fork			*data;  // 
	pthread_mutex_t *instance; // mutex 
} t_mutex;

typedef struct s_mutex  // acces
{
	int				*locked = 0; // set to 1 mutex off to stop threads 
	int				*use = 0; // + 1 chaque use
	long			*last = get_millis(); // use of locked
	long			*starting = get_millis(); //starting
	void			*data = NULL;  // 
	pthread_mutex_t *instance; // mutex 
} t_mutex;
