// Processes
pid_t fork(void);
int execve(const char *filename, char *const argv[], char *const envp[]);
pid_t wait(int *status);
pid_t waitpid(pid_t pid, int *status, int options);
void _exit(int status);
WIFEXITED(); // macro
WEXITSTATUS(); // macro

// Threads

int  pthread_create(pthread_t  *  thread, pthread_attr_t * attr, 
                    void *(*start_routine)(void *), void * arg);
void pthread_exit(void *retval);
int pthread_join(pthread_t th, void **thread_return);
pthread_t pthread_self(void);

// Mutexes/Locks

pthread_mutex_t fastmutex = PTHREAD_MUTEX_INITIALIZER;
int  pthread_mutex_init(pthread_mutex_t  *mutex, 
                        const pthread_mutex_attr_t *mutexattr);
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_trylock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
int pthread_mutex_destroy(pthread_mutex_t *mutex);

// Condition Variables

pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
int    pthread_cond_init(pthread_cond_t    *cond,    pthread_condattr_t
			 *cond_attr);
int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);
int pthread_cond_signal(pthread_cond_t *cond);
int pthread_cond_broadcast(pthread_cond_t *cond);
int pthread_cond_destroy(pthread_cond_t *cond);

// POSIX Semaphores

int sem_init(sem_t *sem, int pshared, unsigned int value);
int sem_wait(sem_t *sem);
int sem_trywait(sem_t *sem);
int sem_post(sem_t *sem);
int sem_getvalue(sem_t *sem, int *sval);
int sem_destroy(sem_t *sem);

// File System

int open(const char *pathname, int flags);
int open(const char *pathname, int flags, mode_t mode);
//        flags: O_RDONLY, O_WRONLY, O_RDWR, O_CREAT, O_EXCL, O_APPEND
//        mode: S_IRWXU, S_IRUSR, S_IWUSR, S_IXUSR, S_IRWXG, S_IRGRP, 
//              S_IWGRP, S_IXGRP, S_IRWXO, S_IROTH, S_IWOTH, S_IXOTH
int close(int fd);
ssize_t read(int fd, void *buf, size_t count);
ssize_t write(int fd, const void *buf, size_t count);
void *mmap(void *start, size_t length, int prot, int flags,
           int fd, off_t offset);
//        prot: PROT_NONE, PROT_EXEC, PROT_READ, PROT_WRITE
//        flags: MAP_FIXED, MAP_SHARED, MAP_PRIVATE
int munmap(void *start, size_t length);
int msync(void *start, size_t length, int flags);
off_t lseek(int fildes, off_t offset, int whence);
//       whence: SEEK_SET, SEEK_CUR, SEEK_END

// Strings

// Safe functions
size_t strlen(const char *s);
char *strncat(char *dest, const char *src, size_t n);
int strncmp(const char *s1, const char *s2, size_t n);
char *strncpy(char *dest, const char *src, size_t n);
char *strndup(const char *s, size_t n);

// Unsafe functions
char *strcat(char *dest, const char *src);
int strcmp(const char *s1, const char *s2);
char *strcpy(char *dest, const char *src);
char *strdup(const char *s);

