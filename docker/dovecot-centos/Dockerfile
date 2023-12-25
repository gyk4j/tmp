# syntax=docker/dockerfile:1

FROM centos
WORKDIR /

RUN cd /etc/yum.repos.d/
RUN sed -i 's/mirrorlist/#mirrorlist/g' /etc/yum.repos.d/CentOS-*
RUN sed -i 's|#baseurl=http://mirror.centos.org|baseurl=http://vault.centos.org|g' /etc/yum.repos.d/CentOS-*

RUN yum install -y dovecot && \

COPY dovecot.conf /etc/dovecot/dovecot.conf

CMD ["/bin/bash"]
#EXPOSE 3000
