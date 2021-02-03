cd Backend \
&& sudo docker build -t prryplatypus/calcback:latest . \
&& sudo docker push prryplatypus/calcback \
&& cd ../Frontend \
&& sudo docker build -t prryplatypus/calcfront:latest . \
&& sudo docker push prryplatypus/calcfront