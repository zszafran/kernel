FROM gentoo/portage
FROM gentoo/stage3-amd64

COPY --from=gentoo/portage /var/db/repos/gentoo /var/db/repos/gentoo

COPY portage /etc/portage
COPY world /var/lib/portage/world

RUN mkdir -p /var/db/repos/crossdev/{profiles,metadata}
RUN echo 'crossdev' > /var/db/repos/crossdev/profiles/repo_name
RUN echo 'masters = gentoo' > /var/db/repos/crossdev/metadata/layout.conf

ENV BAZEL_JAVAC_OPTS="-J-Xms4g -J-Xmx4g"

RUN emerge -u world
RUN crossdev --stage1 --stable --target i686-elf -oO /var/db/repos/crossdev
RUN crossdev --stage1 --stable --target x86_64-elf -oO /var/db/repos/crossdev
RUN rm -rf /usr/portage/distfiles/*

RUN export JAVA_HOME="$(java-config --jdk-home)" 

RUN sh -c "$(curl -fsSL https://raw.githubusercontent.com/robbyrussell/oh-my-zsh/master/tools/install.sh)"
RUN go get github.com/bazelbuild/buildtools/buildifier
COPY zshrc /root/.zshrc

CMD /bin/zsh -l