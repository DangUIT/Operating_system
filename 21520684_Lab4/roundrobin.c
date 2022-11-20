#include <stdio.h>
// Dinh nghia cau truc process
typedef struct
{
    int number_process;
    int quantum;
    int name;
    int burst_time;
    int start;
    int stop;
    int wating_time;
    int turnaround_time;
} process;

// Doc file
void readFile(process *list_pr, FILE *file)
{
    int i = 0;
    int n;
    do
    {
        process pr;
        n = fscanf(file, "%d %d", &pr.name, &pr.burst_time);
        list_pr[i++] = pr;
    } while (n != -1);

    // Line 1 trong file input la list_pr[0] bao gom so process va quantum
    list_pr->number_process = list_pr[0].name;
    list_pr->quantum = list_pr[0].burst_time;
}
// Ghi file
void writeFile(process *list_pr, FILE *file)
{
    int i = 1, start_time = 0, stop_time = 0;
    float total_turnaround_time = 0;
    float total_wating_time = 0;
    int attempt = list_pr->number_process; // Luu so process vao bien tam a
    for (int i = 1; i <= list_pr->number_process; i++)
    {
        list_pr[i].start = list_pr[i].stop = 0;
    }
    while (attempt)
    {
        if (list_pr[i].burst_time <= list_pr->quantum && list_pr[i].burst_time != 0)
        {
            stop_time = start_time + list_pr[i].burst_time;
            list_pr[i].start = start_time;
            total_wating_time += list_pr[i].start - list_pr[i].stop;
            fprintf(file, "%d %d %d\n", list_pr[i].name, start_time, stop_time);
            printf("%d %d %d\n", list_pr[i].name, start_time, stop_time);
            start_time = stop_time;

            list_pr[i].burst_time = 0;
            list_pr[i].turnaround_time = stop_time;
            list_pr[i].stop = stop_time;
            attempt--;
        }
        if (list_pr[i].burst_time > list_pr->quantum && list_pr[i].burst_time != 0)
        {
            stop_time = start_time + list_pr->quantum;
            list_pr[i].start = start_time;
            total_wating_time += list_pr[i].start - list_pr[i].stop;
            fprintf(file, "%d %d %d\n", list_pr[i].name, start_time, stop_time);
            printf("%d %d %d\n", list_pr[i].name, start_time, stop_time);
            list_pr[i].burst_time = list_pr[i].burst_time - list_pr->quantum;
            list_pr[i].stop = stop_time;
            start_time = stop_time;
        }
        if (i >= list_pr->number_process)
            i = 0;
        i++;
    }
    for (int i = 1; i <= list_pr->number_process; i++)
    {
        total_turnaround_time += list_pr[i].turnaround_time;
    }

    fprintf(file, "%.2f \n", total_wating_time / list_pr->number_process);
    fprintf(file, "%.2f \n", total_turnaround_time / list_pr->number_process);
    printf("%.2f \n", total_wating_time / list_pr->number_process);
    printf("%.2f \n", total_turnaround_time / list_pr->number_process);
}
int main()
{
    process list_pr[100];
    FILE *file_read = fopen("input.txt", "r");
    readFile(list_pr, file_read);
    fclose(file_read);

    FILE *file_write = fopen("output.txt", "w");
    writeFile(list_pr, file_write);
    fclose(file_write);
    return 0;
}