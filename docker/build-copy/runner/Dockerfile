FROM build-copy-builder AS build
FROM alpine

WORKDIR /app
COPY --from=build /app/main /app/main

# Install s6 overlay
ARG S6_OVERLAY_VERSION=3.2.0.0
ADD https://github.com/just-containers/s6-overlay/releases/download/v${S6_OVERLAY_VERSION}/s6-overlay-noarch.tar.xz /tmp
RUN tar -C / -Jxpf /tmp/s6-overlay-noarch.tar.xz
ADD https://github.com/just-containers/s6-overlay/releases/download/v${S6_OVERLAY_VERSION}/s6-overlay-x86_64.tar.xz /tmp
RUN tar -C / -Jxpf /tmp/s6-overlay-x86_64.tar.xz

# Configure s6 to run app as a service
ARG APP=main
RUN mkdir -p /etc/s6-overlay/s6-rc.d/${APP}
COPY s6-overlay/type /etc/s6-overlay/s6-rc.d/${APP}/type
COPY s6-overlay/run /etc/s6-overlay/s6-rc.d/${APP}/run
COPY s6-overlay/finish /etc/s6-overlay/s6-rc.d/${APP}/finish

# Specify s6 service dependencies
RUN mkdir -p touch /etc/s6-overlay/s6-rc.d/user/contents.d/
RUN touch /etc/s6-overlay/s6-rc.d/user/contents.d/${APP}
RUN mkdir -p /etc/s6-overlay/s6-rc.d/${APP}/dependencies.d/
RUN touch /etc/s6-overlay/s6-rc.d/${APP}/dependencies.d/base

# Start s6-overlay and let it indirectly start app.
ENTRYPOINT ["/init"]
