# hostip

Show the IP address assigned to the interface assigned to the default gateway.

Only works on Linux.

## Installation

Build with `make`, and copy the `hostip` binary to a directory in your `$PATH`.

```bash
$ make
$ sudo install -o root hostip /usr/local/bin/
```

## Usage

Just type `host`

```bash
$ hostip 
10.0.0.17
```

## Alternatives

`hostname -i` returns the IP address of the hostname. If your DNS is aware of your host, and you don't have an alias to another IP (like `127.0.0.1` in `/etc/hosts`), using `hostname -i` may be enough for you.
