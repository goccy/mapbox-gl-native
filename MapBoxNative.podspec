Pod::Spec.new do |s|

  mapbox_root    = "$(PODS_ROOT)/../../../mapbox-gl-native"
  s.name         = "MapBoxNative"
  s.version      = "0.0.1"
  s.summary      = ""
  s.description  = ""
  s.homepage     = ""
  s.license      = { :type => 'MIT' }
  s.author       = { "goccy" => "goccy54@gmail.com" }
  s.public_header_files = 'include/mgbl/**/*.h'
  mason_packages     = "#{mapbox_root}/mason_packages"
  variant            = "#{mason_packages}/headers/variant/1.0/include"
  rapidjson          = "#{mason_packages}/headers/rapidjson/1.0.2/include"
  boost              = "#{mason_packages}/headers/boost/1.59.0/include"
  geojsonvt          = "#{mason_packages}/ios-9.2/geojsonvt/3.1.0/include"
  libuv              = "#{mason_packages}/ios-9.2/libuv/1.7.5/include"
  
  header_search_path = "#{mapbox_root}/include #{mapbox_root}/src #{variant} #{rapidjson} #{boost} #{geojsonvt} #{libuv}"
  
  s.xcconfig = {
    HEADER_SEARCH_PATHS: header_search_path
  }

  s.source        = { :git => "git@github.com:mapbox/mapbox-gl-native.git", :tag => "0.0.1" }
  s.source_files  = '*.{h,c,cpp}'
  s.requires_arc  = false
  s.ios.frameworks = 'GLKit', 'ImageIO', 'MobileCoreServices', 'QuartzCore', 'SystemConfiguration'
  s.ios.libraries  = 'c++', 'z', 'sqlite3'

  s.subspec 'source' do |ss|
    ss.source_files = "include/**/*.hpp", "src/**/*.{hpp,cpp}"
  end
  
end
