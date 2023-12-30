FROM centos

RUN cd /etc/yum.repos.d/ && \
  sed -i 's/mirrorlist/#mirrorlist/g' /etc/yum.repos.d/CentOS-* && \
  sed -i 's|#baseurl=http://mirror.centos.org|baseurl=http://vault.centos.org|g' /etc/yum.repos.d/CentOS-*
RUN yum update -y && yum install -y epel-release && yum update -y && yum install -y sendmail sendmail-cf m4 mailx

RUN useradd -m tom
RUN useradd -m jerry

RUN echo 'tom:1234' | chpasswd 
RUN echo 'jerry:1234' | chpasswd

COPY sendmail.mc /etc/mail/sendmail.mc
RUN mkdir /etc/mail/auth
COPY client-info /etc/mail/auth

RUN m4 /etc/mail/sendmail.mc > /etc/mail/sendmail.cf

CMD ["sendmail", "-bD"]
