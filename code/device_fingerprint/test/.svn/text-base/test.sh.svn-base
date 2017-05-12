while read line
do
	data=$line
	url="http://10.20.22.11:8080/appsvr/cgi_device_fingerprint"
	curl -l -H "Content-type: application/json" -d "{\"data\":\"$data\"}" $url
	#ab -n 10000 -c 100 "$url" >> ab.t.out
	echo ""
	#echo $data
	#echo $line
done
