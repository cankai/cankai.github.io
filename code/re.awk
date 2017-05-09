awk -F"|" '$2 ~ /chen/ && $4 ~ /read/ {print $2,$4}' txt
