#' Fit a model with RStan
#'
#' @param lastday
#' @param num
#'
#' @return out
#' @export
#'
#' @examples
#' fit <- stanBstsFit(100)
stanBstsFit <- function(num = NULL, lastday = NULL){
  # Input today's date and reported number
  nday <- Sys.Date()
  nval <- num

  # Download the raw CSV file
  # https://ckan.pf-sapporo.jp/datastore/dump/7dc6b374-ac73-4df4-b899-ea6c8cac3e32
  # https://ckan.pf-sapporo.jp/api/3/action/datastore_search?resource_id=7dc6b374-ac73-4df4-b899-ea6c8cac3e32&limit=32000&records_format=csv
  d <- read.csv("https://ckan.pf-sapporo.jp/datastore/dump/7dc6b374-ac73-4df4-b899-ea6c8cac3e32")
  d3 <- data.frame(day = d[, 2], num = d[, 3])
  d3$day <- as.Date(d3$day) # Put date into Date class

  # Fill NAs by 0
  d3[which(is.na(d3$num)), 2] <- 0
  if(is.null(lastday)){
    # Add the latest value MANUALLY
    d3[(nrow(d3) + 1), 1] <- nday
    d3[nrow(d3), 2] <- nval
    d3$num <- as.numeric(d3$num)
  }

  # Remove duplicates
  d4 <- dplyr::distinct(d3, day, .keep_all = T)

  if(!is.null(lastday)){
    idx <- which(d4$day == lastday)
    d4 <- d4[1:idx, ]
  }

  # Set up Stan env
  options(mc.cores = parallel::detectCores())
  rstan::rstan_options(auto_write = TRUE)

  # Data as a list
  N <- nrow(d4)
  y <- d4$num
  dat <- list(N = N, y = y)

  # Fit by Stan
  fit <- rstan::sampling(stanmodels$tokbsts, data = dat,
                     iter = 1000, chains = 4, verbose = T)

  out <- list()
  out$df <- d4
  out$fit <- fit
  return(out)
}

#' Compute fitted values
#'
#' @param out
#'
#' @return val
#' @export
#'
#' @examples
#' val <- fitValue(out)
fitValue <- function(out){
  # Extract MCMC samples to obtain MLE parameters
  N <- nrow(out$df)

  fit.smp <- rstan::extract(out$fit)
  trend <- rep(0, N)
  for (i in 1:N) {
    tmp <- density(fit.smp$trend[, i])
    trend[i] <- tmp$x[tmp$y == max(tmp$y)]
  }
  trend_h <- rep(0, N)
  for (i in 1:N) {
    tmp <- fit.smp$trend[, i]
    trend_h[i] <- quantile(tmp, probs = 0.8)
  }
  trend_l <- rep(0, N)
  for (i in 1:N) {
    tmp <- fit.smp$trend[, i]
    trend_l[i] <- quantile(tmp, probs = 0.2)
  }
  season <- rep(0, N)
  for (i in 1:N) {
    tmp <- density(fit.smp$season[, i])
    season[i] <- tmp$x[tmp$y == max(tmp$y)]
  }
  # Fitted time series
  fitted <- cumsum(trend) + season

  val <- list()
  val$fitted <- fitted
  val$trend <- trend
  val$trend_h <- trend_h
  val$trend_l <- trend_l
  val$season <- season
  return(val)
}

#' Plot summary, trend, and seasonality
#'
#' @param val
#' @param out
#' @param saveFile
#'
#' @return
#' @export
#'
#' @examples
#' plotOutput(val, out, saveFile = T)
plotOutput <- function(val, out, saveFile = F){
  # Create a title with start and end dates
  df <- out$df
  mtitle <- paste0('Sapporo, daily from ', df$day[1], ' to ', df$day[nrow(df)])

  y <- out$df$num
  pred <- val$fitted
  trend <- val$trend
  season <- val$season
  # Plot
  matplot(cbind(y, pred, cumsum(trend)),
          type = 'l', lty = c(1, 3, 1), lwd = c(1, 2, 3), col = c(1, 2, 4),
          ylab = '', main = mtitle)
  legend('topleft',
         legend = c('Reported', '2nd-diff Trend + Seasonality', '2nd-diff Trend'),
         lty = c(1, 3, 1), lwd = c(1, 2, 3), col = c(1, 2, 4))
  plot(trend, type = 'l', lwd = 2)
  plot(season, type = 'l', lwd = 2)

  # Plot for PNG files
  if(saveFile){
    png(filename = 'covid19_fit_summary.png', width = 720, height = 540)
    matplot(cbind(y, pred, cumsum(trend)),
            type = 'l', lty = c(1, 3, 1), lwd = c(1, 2, 3), col = c(1, 2, 4),
            ylab = '', main = mtitle)
    legend('topleft',
           legend = c('Reported', '2nd-diff Trend + Seasonality', '2nd-diff Trend'),
           lty = c(1, 3, 1), lwd = c(1, 2, 3), col = c(1, 2, 4), cex = 1.5)
    dev.off()

    png(filename = 'covid19_fit_trend.png', width = 720, height = 540)
    plot(trend, type = 'l', lwd = 2)
    dev.off()

    png(filename = 'covid19_fit_season.png', width = 720, height = 540)
    plot(season, type = 'l', lwd = 2)
    dev.off()
  }
}

#' Plot of cases by generations
#'
#' @param out
#' @param saveFile
#'
#' @return
#' @export
#'
#' @examples
#' plotGens(saveFile = T)
plotGens <- function(out = NULL, saveFile = F){
  if(is.null(out)){
    # Download the original dataset
    d <- read.csv('https://stopcovid19.metro.tokyo.lg.jp/data/130001_tokyo_covid19_patients.csv')
    # Trace each generation
    da1 <- data.frame(day = d[, 5], age = d[, 9], num = 1)
    da1$day <- as.Date((da1$day))
    da2.tmp1 <- dplyr::group_by(da1, day, age)
    da2.tmp2 <- dplyr::summarise(da2.tmp1, sum(num))
    da2 <- as.data.frame(da2.tmp2)

    # Set up a consecutive date vector
    dayseq <- seq(from = as.Date(da2$day[1], origin = '1970-01-01'),
                  to = as.Date(da2$day[nrow(da2)], origin = '1970-01-01'),
                  by = 'day')
    dayseq <- as.data.frame(dayseq)
    names(dayseq) <- 'day'

    da3 <- dplyr::left_join(dayseq, da2, by = 'day')
    names(da3)[3] <- 'num'
    da3[which(is.na(da3$num)), 3] <- 0
    da4 <- da3[2045:(nrow(da3)), ]
  } else {
    da4 <- out$gen.df
  }

  gtitle <- paste0('Tokyo, daily from ',
                   da4$day[1], ' to ', da4$day[nrow(da4)], ' by generations')
  matplot(cbind(da4[da4$age == '20代', 3],
                da4[da4$age == '30代', 3],
                da4[da4$age == '40代', 3],
                da4[da4$age == '50代', 3],
                da4[da4$age == '60代', 3],
                da4[da4$age == '70代', 3],
                da4[da4$age == '80代', 3]),
          type = 'l', lty = 1, xlab = '', ylab = '',
          main = gtitle)
  legend('topleft',
         legend = c('20s', '30s', '40s', '50s', '60s', '70s', '80s'),
         lty = 1, col = c(1, 2, 3, 4, 5, 6, 7), ncol = 2)

  if(saveFile){
    jpeg(filename = 'covid19_fit_generation.jpg', width = 720, height = 540)
    matplot(cbind(da4[da4$age == '20代', 3],
                  da4[da4$age == '30代', 3],
                  da4[da4$age == '40代', 3],
                  da4[da4$age == '50代', 3],
                  da4[da4$age == '60代', 3],
                  da4[da4$age == '70代', 3],
                  da4[da4$age == '80代', 3]),
            type = 'l', lty = 1, xlab = '', ylab = '',
            main = gtitle)
    legend('topleft',
           legend = c('20s', '30s', '40s', '50s', '60s', '70s', '80s'),
           lty = 1, col = c(1, 2, 3, 4, 5, 6, 7), ncol = 2)
    dev.off()
  }
}

#' Texts for reporting on Twitter
#'
#' @param val
#' @param num
#'
#' @return
#' @export
#'
#' @examples
#' textOutput(val, 100)
textOutput <- function(val, num){
  # Obtain variables
  trend <- val$trend
  season <- val$season
  # Set up a description for reporting on Twitter
  ctrend <- cumsum(trend)
  sentence1 <- paste0("本日の札幌市の報告数は", num, "名、",
                      "二階差分トレンドの直近7日間の推定値は",
                      signif(rev(ctrend)[7], 3), ", ",
                      signif(rev(ctrend)[6], 3), ", ",
                      signif(rev(ctrend)[5], 3), ", ",
                      signif(rev(ctrend)[4], 3), ", ",
                      signif(rev(ctrend)[3], 3), ", ",
                      signif(rev(ctrend)[2], 3), ", ",
                      signif(rev(ctrend)[1], 3),
                      "、",
                      "7日周期成分の推定値は",
                      signif(rev(season)[7], 3), ", ",
                      signif(rev(season)[6], 3), ", ",
                      signif(rev(season)[5], 3), ", ",
                      signif(rev(season)[4], 3), ", ",
                      signif(rev(season)[3], 3), ", ",
                      signif(rev(season)[2], 3), ", ",
                      signif(rev(season)[1], 3),
                      "、",
                      "トレンドの直近3日間の差分値は",
                      signif(rev(trend)[3], 3), ", ",
                      signif(rev(trend)[2], 3), ", ",
                      signif(rev(trend)[1], 3), "。"
  )

  sentence4 <- paste0("使用したRパッケージはこちら https://github.com/kn1kn1/SapporoCovidMonitor")
  print(sentence1)
  print(sentence4)
}

