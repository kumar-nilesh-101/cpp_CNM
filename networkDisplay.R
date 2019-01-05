library(igraph)
library(randomcoloR)

 #matrix.File <- read.line(prompt = "Enter path of the `.csv` file containing data for adjacency matrix : ")
 adj.matrix <- read.csv(file = "D:\\communityDetection\\adj.csv", header = FALSE, sep = ",")
 adj.matrix<- as.matrix(adj.matrix)
 
 #communities.File <- read.line(prompt = "Enter path of the `.csv` file containing communities metadata : ") 
 communities <- read.csv(file = "D:\\communityDetection\\communities.csv", header = FALSE, sep = ",")
 communities <- as.matrix(communities)
 
 for(i in 1:nrow(communities))
 {
    for(j in 1:ncol(communities))
    {
        if(! is.na(communities[i, j]))
        {
            communities[i, j] <- communities[i, j] + 1
        }
    }
 }
 
 d <- c(1:nrow(adj.matrix))
 g <- graph_from_adjacency_matrix(adj.matrix, mode = "undirected", diag = FALSE)
 V(g)$name <- d
 colorSpace <- distinctColorPalette(k = nrow(communities), altCol = FALSE, runTsne = FALSE)

 for(i in 1 : length(d))
 {
    for(j in 1 : nrow(communities))
    {
        if(d[i] %in% communities[j, ])
	  {
		V(g)$color[i] = colorSpace[j]
        }
    }
 }
 
 plot(g)