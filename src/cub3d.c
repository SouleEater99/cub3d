/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-maim <ael-maim@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 04:00:00 by ael-maim          #+#    #+#             */
/*   Updated: 2024/10/09 04:00:17 by ael-maim         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void    Ft_Free_All(char *Msg, t_data *Data, int Exit_Status)
{
    if (Data)
    {
        if (Data->Mlx_Win)
            mlx_destroy_window(Data->Mlx , Data->Mlx_Win);
        if (Data->Mlx)
            mlx_destroy_display(Data->Mlx);
        
    }
    if (Msg)
        write(2, Msg, strlen(Msg));
    exit(Exit_Status);
}

t_data  *Init_Data()
{
    t_data *Data;

    Data = (t_data *)malloc(sizeof(t_data));
    if (!Data)
        return (NULL);
    Data = memset(Data, 0, sizeof(t_data));

}

void    Init_Mlx(t_data *Data)
{
    Data->Mlx = mlx_init();
    if (!Data->Mlx)
        Ft_Free_All("Mlx Fail\n", Data, 1);
    Data->Mlx_Win = mlx_new_window(Data->Mlx, Data->Width, Data->High, "First Game 3D");
    if (!Data->Mlx_Win)
        Ft_Free_All("Mlx_Win Fail\n", Data, 1);
    
}

int main()
{
    t_data  *Data;
    char *Map[] = {
        "111111111111111111",
        "100000001000000001",
        "100000000000110001",
        "100000001000110001",
        "100011011110110001",
        "100000001000000001",
        "100000000000000001",
        "100000001000000001",
        "111111111111111111",
    };

    Data = Init_Data();
    Init_Mlx(Data);
}