import requests, getpass

print('Enter the URL of the dataset: ')
url = input() #"https://www.kaggle.com/c/3004/download/train.csv"
print('Enter the username: ')
username = input() #"Your Email"
print('Enter the password: ')
password = getpass.getpass() #"Your Password"

headers = {'User-Agent': 'Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/64.0.3282.186 Safari/537.36', 'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,*/*;q=0.8', 'Accept-Encoding': 'gzip, deflate','Accept-Language': 'en-US,en;q=0.9,hi;q=0.8'}


#Login and capture the cookies

try:
	post_data = {'username':username, 'password': password}
	res = requests.post('https://www.kaggle.com/account/login', headers=headers, data=post_data, allow_redirects=False)


	#Cookie: .ASPXAUTH=4EC0ACCA24AF121F35CDF2AAF6607116BA3DE9F2AD2A253F5011EB85C89293D0DC7E4E7BB1929CAC5BB459D23B5AA67D3DB354A9AB0210BA2E5F7D389BFCF6C978B424764C2CB271C9F5C284DA67E02396A9629A; ARRAffinity=a4491c4997833d3ba8f463815b87223517e23a18775a9e2cc57d79051f60da03; intercom-lou-koj6gxx6=1; TempData=.vwdWXCOwxHvxtQSaSj/h+msgJeOkjecLzmomLSn57239VC/rzStVq/YtYoAh5OLxgO1ZE98b0vYrlmM3NvBba4pE+w8=

	headers['Cookie'] = res.headers['Set-Cookie'].split('domain=.kaggle.com;')[0] #For the cookie .ASPXAUTH
	headers['Cookie'] += res.headers['Set-Cookie'].split('HttpOnly, ')[1].split(' path')[0] #For the cookie TempData
	headers['Cookie'] += res.headers['Set-Cookie'].split('HttpOnly, ')[2].split('Path')[0] #For the cookie ARRAffinity

	print('\nLogged in successfully..')

except:
	print('\nLogin failed. Please check the credentials and try again..')
	exit()

#Download the file


res = requests.get(url, headers=headers, allow_redirects=True, verify=False, stream=True)

size = 0

print("\n")

with open('data.csv', 'wb') as f:
	for chunk in res.iter_content(chunk_size=1024*512): #In chunks of 512 KB 
		if chunk:
			size += len(chunk)
			print('\r'+str(size/(1024*1024))+' MB downloaded',end="")
			f.write(chunk)

f.close()
print('\r'+str(size/(512*1024*1024))+' MB downloaded')
print('Download complete. Saved as data.csv')