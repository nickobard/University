# build stage - conda takes a lot of memory (~1.4GB), so we will use it only
# in build stage, where it will create environment and export it to virtual environment,
# which will be used in the runtime image without conda memory overhead.
FROM continuumio/miniconda3:latest AS build-stage

COPY ../environment.yml ./

RUN conda env create -f environment.yml

# install from conda-forge channel conda-pack package
RUN conda install -c conda-forge conda-pack

RUN conda-pack -n bipyt-sp -o /tmp/env.tar && \
    mkdir /venv && cd /venv && tar xf /tmp/env.tar && \
    rm /tmp/env.tar

RUN /venv/bin/conda-unpack

# Runtime image, much more smaller that conda image
FROM debian:buster AS runtime-stage

WORKDIR /app

# Copy exported virtual environment from last build stage to this runtime image.
COPY --from=build-stage /venv /venv

SHELL ["/bin/bash", "-c"]

ENTRYPOINT source /venv/bin/activate && cd app/app/ && \
uvicorn main:app --proxy-headers --host 0.0.0.0 --port 8000
