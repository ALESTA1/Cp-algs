struct DSU{

    ll parent[20001];
    ll size[20001];

    void make_set(ll x){
        parent[x]=x;
        size[x]=1;
    }

    ll find_set(ll x){
        if(parent[x]==x)
            return x;
        return parent[x] = find_set(parent[x]);
    }

    void unite_sets(ll x,ll y){
        x = find_set(x);
        y = find_set(y);

        if(x!=y){
            if(size[x]<size[y])
                swap(x,y);
            parent[y] = x;
            size[x]+=size[y];
        }
    }
};