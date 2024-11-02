from pythonping import ping

def ping_host(host):
    try:
        request = ping(target=host, count=3, timeout=2)

        loss = request.packet_loss

        if loss < 1:
            return f"{host}: Online"
        else :
            return f"{host}: Offline"
      

    except OSError:
        return "ping failed"
    
    

        # 'host': host,
        # 'avg_latency': ping_result.rtt_avg_ms,
        # 'min_latency': ping_result.rtt_min_ms,
        # 'max_latency': ping_result.rtt_max_ms,
        # 'packet_loss': ping_result.packet_loss


hosts = [
    '172.66.15.255'
]

for host in hosts:
    print(ping_host(host))