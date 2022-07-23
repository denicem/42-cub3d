
i=1000
while [ $i -le 86 ]
do
	./cub3D ./maps/map.cub &
	pkill -9 cub3D
	i=$(($i + 1))
done
